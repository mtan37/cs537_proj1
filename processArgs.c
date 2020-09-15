#include <stdlib.h>
#include <stdio.h>

int MAX_PID_LENGTH;
typedef struct flags{
    int flag_p = 0;//specifies the pid of the process that needs to be displayed. If not present, print all process owned by the current user
    int flag_s = 0;//display single-character state info about the process. If not present, default to false
    int flag_U = 0;//Display the amount of user time consumed by the process. If not present, default to true
    int flag_S = 0;//Display the amount of sytem time consumed by the process. If not present, default to false
    int flag_v = 0;//Display the amount of virtual memory currently being used (in pages) by this program.
    int flag_c = 0;//Display the command-line that started the process. Default to true
    char *content_p;
}

int processArguments(char **arg){
    int count = 0;
	//check to see if it is a flag(start with -?)
	if(*arg[count]=='-'){
        //check if the length is valid(length = 2?)
		//if the lenght is valid, doe
		//if it is a flag, swith the corresponding flag variable to 1
		
		//if it is a p flag, read the next argument as well which supplies the pid
    }
	//else
	else{
		//if it is not a flag, return an error
	}
}

/**
 * Check whether a pid is valid number string//TODO: wait for Joe's reply on what struc to use for pid
 */
int checkPid(){
	
}
