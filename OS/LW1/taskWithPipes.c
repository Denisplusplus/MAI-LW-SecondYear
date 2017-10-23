#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
 
typedef struct StringMatchCheck {
    char original[250];
    char pattern[250];
    char result[17];
} StringMatchCheck;
 
int main(){
    StringMatchCheck MatchCheck;
    printf("Write original string\n"); 
    scanf("%s", MatchCheck.original);	    // reading Original string from console
   
    printf("Write pattern string\n");
    scanf("%s", MatchCheck.pattern);		// reading Pattern string from console
   

   
    int pipeoparent[2];
    int pipeToChild[2];
    pipe(pipeToParent); // creating pipes
    pipe(pipeToChild);
 
    pid_t child;
    child = fork();

    if(child < 0) {
        printf("CREATE_FAILED");
        exit(-1);
    } else if (child > 0){
        close(pipeToParent[0]);
        write(pipeToParent[1], &MatchCheck, sizeof(MatchCheck));
        close(pipeToParent[1]);
 
        close(pipeToChild[1]);
        read(pipeToChild[0],&MatchCheck,sizeof(MatchCheck));
        printf("%s\n", MatchCheck.result);
        close(pipeToChild[0]);
    } else { 
        close(pipeToParent[1]);
        read(pipeToParent[0],&MatchCheck,sizeof(MatchCheck));
        close(pipeToParent[0]);
    // BEGIN STRINGS CHECKING  
        StringMatchCheck* newCheck =  &MatchCheck;                                
        char* indicator;
        if ((indicator=strstr(newCheck->original, newCheck->pattern)) != NULL) {
        	strcpy(newCheck->result, "Matches found");
        } else {
        	strcpy(newCheck->result, "No matches found");
        }
    // END STRINGS CHECKING  
        close(pipeToChild[0]);
        write(pipeToChild[1], newCheck, sizeof(*newCheck));
        close(pipeToChild[1]);
    }
}
