#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

char currentpath[FILENAME_MAX];

void byteCalculator(int input)
{
    if(input / 1024000000 > 0) {
	printf("%ldG\t", input / 1024000000);
	return;
	}
    if(input / 1024000 > 0) {
	printf("%ldM\t", input / 1024000);
	return;
	}
    if(input / 1024 > 0){
	printf("%ldK\t", input / 1024);
	return;
	}
    else
	printf("%ld\t", input);
}

void linearPrintDir(const char *name)
{
    DIR *dir = opendir(name);
    struct dirent *entry;
    struct stat mystat;
    if(dir != NULL)
    {
        while(entry = readdir(dir))
	    {
            char newStr[1024];
            sprintf(newStr, "%s%s", name, entry->d_name);
	        stat(newStr, &mystat);
	        byteCalculator(mystat.st_size);
            if(entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
                sprintf(newStr, "%s/", newStr); //add a slash to the end for recursion purposes 
                printf("trying to recurse on file name %s\n", newStr);
                linearPrintDir(newStr);
            }  
            else{
                printf("%s\n", newStr);
            }
	    }
    closedir(dir);
    }
}

int main(int argc, char* argv[])
{
    int i = 0;
    for(i = 0; i < argc; i++)
    {
   	 linearPrintDir(argv[i]);
    }
    return 0;
}
