#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h> // options flags
#include <inttypes.h>
#include <errno.h>

#define BUFFER_SIZE 256

void rename_file(char * oldfilename, char* newfilename) {
	if (rename(oldfilename, newfilename) == -1) {
		perror("Error while 'rename' \n");
	}

}

int main(void) {
	char* str = "This string was created in this file by system call\n";
	char* oldfilename ="old";
	char buffer[BUFFER_SIZE];
	int fd, w; 
	fd = creat(oldfilename, S_IREAD | S_IWRITE);
	if (fd == -1) {
		perror("Error while 'creat' ");
	} else {
		printf("File with filenasme 'old' was created \n");
	}

	if (w = write(fd, str, strlen(str)) == -1 ) {
		perror("Error while 'write' \n");
	} 
	if (fsync(fd) == -1) {
		perror("Error while 'fsync' \n");
	}
	if (close(fd) == -1) {
		perror("Error while 'close'\n");
	}

	char newfilename[20];
	printf("Enter new filename to rename 'old' \n");
	scanf("%s", newfilename);
	rename_file(oldfilename, newfilename);
	fd = open(newfilename, O_RDWR);
	if (read(fd, buffer, strlen(str)) == strlen(str)) {
		fprintf(stdout, "%s",buffer);
	} else {
		perror("Error while 'read'\n");
	}
	if (close(fd) == -1) {
		perror("Error while 'close'\n");
	}


	char dirname[20];
	printf("Enter a dirname to create new folder \n");
	scanf("%s", dirname);


	if (mkdir(dirname, 0755) == -1) {
		perror("Error while 'mkdir' \n");
	}


	if (unlink(newfilename) == -1) {
		perror("Error while unlink\n");
	}

	pid_t pid = fork();
    if (pid == 0) {
        fprintf(stdout, "It's child process, pid = ");
        fprintf(stdout, "%ld\n", (intmax_t)getpid());
        fprintf(stdout, "Parent's pid = ");
        fprintf(stdout, "%ld\n", (intmax_t)getppid());
    } else if (pid > 0) {
        fprintf(stdout, "It's parent process, pid = ");
        fprintf(stdout, "%ld\n", (intmax_t)getpid());
        fprintf(stdout, "Parent's pid = ");
        fprintf(stdout, "%ld\n", (intmax_t)getppid());
        wait(NULL);
    } else if (pid == -1) {
        perror("Error fork");
	}
	return 0;


}
