#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]){
    DIR *dir;
    struct dirent   *drnt;
    
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
        printf("%s ",drnt->d_name);
    }
    printf("\n");
    closedir(dir);
    return 0;
}
