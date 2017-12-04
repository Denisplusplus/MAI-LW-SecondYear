#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/io.h>
#include <sys/mman.h>
#include "FileProcessor.h"

void menu(void);

int main(int argc, char const *argv[]) {
	int fd; 
	struct stat fileStat;
	char fileName[256]; char newString[256]; char oldString[256];
	int size = 0; int numberOfString;
	int choise;

	int action = Filter(argc, argv);
	switch(action) { //Single String Mode
		case 1: 
		{
			GetInfo(fd, size, argv[1]); // RAM limit isn't specified by user
			break;
		}	
		case 2: 
		{
			GetStringPrint(fd, size, argv[1], atoi(argv[3]));
			break;
		}
		case 3: 
		{
			GetInfo(fd, atoi(argv[2]), argv[1]);
			break;
		}
		case 4:
		{
			GetStringPrint(fd, atoi(argv[2]), argv[1], atoi(argv[3]));
			break;
		}	
		case 5:
		{
			GetStringSearch(fd, size, argv[1], argv[3]);
			break;
		}
		case 6:
		{
			GetStringSearch(fd, atoi(argv[2]), argv[1], argv[4]);
			break;
		}
		case 7:
		{
			GetStringReplace(fd, size, argv[1], argv[3], argv[4]);
			break;
		}
		case 8:
		{	
			GetStringReplace(fd, atoi(argv[2]), argv[1], argv[4], argv[5]);
			break;
		}
		case 10:
		{
			Information();
			break;
		}
		case 11: // Interactive Mode
		{	
			do {
				Menu();
				scanf("%d", &choise);
				switch(choise) {
					case 1:
						printf("Input filename\n");
						scanf("%s", fileName);
						break;
					case 2:
						GetInfo(fd, atoi(argv[1]), fileName);
						break;	
					case 3:
						printf("Input number of string\n");
						scanf("%d", &numberOfString);
						GetStringPrint(fd, atoi(argv[1]), fileName, numberOfString);
						break;	
					case 4:
						printf("Input the string to replace\n");
						scanf("%s", oldString);
						printf("Input a new string\n");
						memset(newString, '\0', 256);
						scanf("%s", newString);
						GetStringReplace(fd, atoi(argv[1]), fileName, oldString, newString);
						break;	
					case 0:
						break;	
				}
			} while (choise!=0);
			
		}

	}

	
	return 0;
}

