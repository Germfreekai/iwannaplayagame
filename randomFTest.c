#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

typedef struct
{

	int flag; 
	long int size_f;
	char* dir_n;
	char* file;
	char* ex_n;

}Args; 

// Thread for navigate and count new Dir
void* foundNewDir(void* vargs); 
off_t Fsize(const char* filename); 
char* getName(char* arg); 

int main(int argc, char* argv[argc+1])
{

	// assert(argc == 2 && "ERR: Wrong usage || Correct form: ./FILENAME <directory>");

	// Initialize struct (args)
	Args* dirInf = (Args*)malloc(sizeof(Args));
	dirInf->flag = 1;
	dirInf->size_f = 17000; 
	dirInf->dir_n = "../..";
	dirInf->file = (char*)calloc(100,sizeof(char));

	// Name of file 
	dirInf->ex_n = getName(argv[0]);

	printf("File name: %s\n", dirInf->ex_n); 

	// Thread vars
	pthread_t fnd_t; 
	int fnd; 

	// Create main thread
	fnd = pthread_create(&fnd_t, NULL, foundNewDir, (void*)dirInf);
	pthread_join(fnd_t, NULL); 

	printf("Selected file from MAIN: %s\n", dirInf->file); 

	// Free memory
	free(dirInf->file);
	free(dirInf->ex_n);
	free(dirInf); 

	return EXIT_SUCCESS; 

}

// Compartimos memoria en el Struct
void* foundNewDir(void* vargs)
{

	Args* dirInf = (Args*)vargs; 

	// Struct for dirs
	DIR* dir; 
	struct dirent* drnt; 

	// New thread
	pthread_t ndir_t;
	int ndir;

	// For current dir
	char cwd[1000]; 
	char* newPath;

	// Change to user's dir
	chdir(dirInf->dir_n); 

	// Get directory
	getcwd(cwd, sizeof(cwd)); 

	//dirInf->dir_n = cwd; 
	//strcat(dirInf->dir_n, "/");

	printf("cwd before dir read: %s\n", dirInf->dir_n);

	// Open directory
	dir = opendir(dirInf->dir_n); 
	if(dir == NULL)
	{

		printf("ERR: Invalid dir: %s\n", dirInf->dir_n);
		pthread_exit(0); 

	}


	// While over returned files / directories
	while((drnt = readdir(dir)) != NULL)
	{
		// strcmp returns 0 if equal
		// Skip father and current dierctory
		if(!strcmp(drnt->d_name, ".") || !strcmp(drnt->d_name, "..") || !strcmp(drnt->d_name, dirInf->ex_n))
		{

			continue;

		}
		// If directory
		// Create new thread
		else if(drnt->d_type == DT_DIR)
		{

			// New path
			newPath = cwd;
			strcat(newPath,"/");
			
			// Path to new path
			strcat(newPath, drnt->d_name);

			// Pass new directory
			dirInf->dir_n = newPath;

			printf("cwd after dir read: %s\n", dirInf->dir_n);
	
			// Create new thread for new directory
			ndir = pthread_create(&ndir_t, NULL, foundNewDir, (void*)dirInf);
			pthread_join(ndir_t, NULL);

			// Go up a level
			chdir(".."); 
			getcwd(cwd, sizeof(cwd));

			// Retrun to father directory
			dirInf->dir_n = cwd; 
			

		}
		// Print files
		else
		{
			// If file bigger
			if(Fsize(drnt->d_name) > dirInf->size_f)
			{
				
				// Only first found	
				 if(dirInf->flag)
				{

					dirInf->flag = 0;

					// Get current path
					getcwd(cwd, sizeof(cwd)); 

					// Get path + /
					newPath = cwd;
					strcat(newPath, "/");

					// Add selected file
					strcat(newPath, drnt->d_name);
					strcpy(dirInf->file, newPath);


				}
				
			}
			
		}

	}

	// Close
	closedir(dir); 

	// Exit thread
	pthread_exit(EXIT_SUCCESS); 

}

off_t Fsize(const char* filename)
{

	struct stat st;

	if(stat(filename, &st) == 0)
	{

		return st.st_size;

	}
	else
	{

		fprintf(stderr, "Could not determine size of file: %s || %s\n", filename, strerror(errno));

		return -1; 

	}

}

char* getName(char* arg)
{

	char* fname = arg; 
	char* rname = (char*)calloc(15, sizeof(char)); 

	size_t s = 0; 

	for(size_t i = strlen(fname)-1; i > 0; i--)
	{

		if(fname[i] == '/')
		{

			s = i; 

		}

	}

	int c = 0; 

	for(size_t i = s + 1; i < strlen(fname); i++)
	{

		rname[c] = fname[i]; 

		c++; 

	}

	return rname; 

}
