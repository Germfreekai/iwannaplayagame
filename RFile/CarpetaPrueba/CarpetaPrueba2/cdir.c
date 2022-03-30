#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int dircount = 0;
	DIR *dir;			   
  struct dirent   *drnt;			   
  /*Check correct usage*/
  if (argc < 2){
    printf("Usage: %s <directory>\n", argv[0]);
    return -1;
  }
  
	dir = opendir(argv[1]);        
	if (dir == NULL){
	  printf("%s: Not a valid directory\n", argv[1]);
    return -1;
  }
        
	while ((drnt = readdir(dir)) != NULL){
		if(!strcmp(drnt->d_name,".")|!strcmp(drnt->d_name,".."))  {
				continue; /*Skip current directory and parent directory*/
		}
		if(drnt->d_type == DT_DIR){
        printf("%s\n", drnt->d_name);
		    dircount ++; /*Count if current file in the stream is a directory (DT_DIR)*/
		}

  }
  printf("Number of dirs: %d\n",dircount);
  closedir(dir);
  return 0;
}
