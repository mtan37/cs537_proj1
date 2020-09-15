#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "processArgs.h"
typedef struct flags{
    int flag_p = -1;//specifies the pid of the process that needs to be displayed. If not present, this value will default to false, and program will print all process owned by the current user
    int flag_s = -1;//display single-character state info about the process. If not present, default to false
    int flag_U = -1;//Display the amount of user time consumed by the process. If not present, default to true
    int flag_S = -1;//Display the amount of sytem time consumed by the process. If not present, default to false
    int flag_v = -1;//Display the amount of virtual memory currently being used (in pages) by this program. If not present,default to false
    int flag_c = -1;//Display the command-line that started the process. Default to true
	int length_p = 0;
    char *content_p;
}

/**
 * Check whether a pid is valid numeric string
 * Return the length of the pid string. If not valid, return 0
 */
int isPidValid(char *pid){
	int pidLength = 0;
	//loop through the string to check whether each character is a number
	while (pid[pidLength]!="\0" && isdigit(pid[pidLength])){
		//increase the length
		pidLength++;
	}
	//check the length
	if(pidLength > 0){
		return pidLength;
	}
	else{
		return 0;
	}
}
/**
 * Chech whether a flag is has valid type
 */
int isFlagValid(){
	//is the flag the right length?
	//is the flag a valid letter type
	//(if it is p_flag)is the flag already used?
		//check whether the p flag variable is set to -1 	
}
/**
 * Set the flags to default value if they are not already set by users
 */
int setFlagsToDefault(){
	//check p flag(default false)
	//TODO: extra credit: will need to change p flag's implementation so user can enter multiple instance of p
	//check s flag(default false)
	//check U flag(default true)
	//check S flag(default false)
	//check v flag(default false)
	//check c flag(default true)
}
/**
 * Print usage to console
 */
void printUsage(){
}
int processArguments(int argc,char **arg){
  	//check if the count of argument is valid
	if(argc > 0 && argc < ){
		int count = 0;
		//check to see if it is a flag(start with -?)
		if(arg[count][0]=='-'){
			//check if the flag is valid
			//process the flag arg
				//swith the corresponding flag variable to 1
				//if it is a p flag, read the next argument as well, which supplies the pid
					//increase the count
			//increase the count
			printf("this is a flag: %s\n", arg[count]);
			}
			else{
			//if it is not a flag, return an error
			printf("Entered an invalid flag: %s \n",);
			}
}
