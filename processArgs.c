#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "processArgs.h"

/**
 *	Initialize flags
 */
flags *initFlags(){
	flags *flagsVar = calloc(1, sizeof(flags));
	flagsVar->flag_p = -1;
	flagsVar->flag_s = -1;
	flagsVar->flag_U = -1;
	flagsVar->flag_S = -1;
	flagsVar->flag_v = -1;
	flagsVar->flag_c = -1;
	flagsVar->length_p = 0;
	return flagsVar;
}


/**
 * Check whether a pid is valid numeric string
 * Return the length of the pid string. If not valid, return 0
 */
int isPidValid(char *pid){
	int pidLength = 0;
	//loop through the string to check whether each character is a number
	while (pid[pidLength]!='\0' && isdigit(pid[pidLength])){
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
	return 0;
}
/**
 * Set the flags to default value if they are not already set by users
 */
void setFlagsToDefault(){
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
void processArguments(int argc,char **argv){
  	//check if the count of argument is valid
	if(argc > 0){
		int count = 1;//start from index 1
		while(count < argc){
			//check to see if it is a flag(start with -?)
			if(argv[count][0]=='-'){
				//check if the flag is valid
				//process the flag arg
					//swith the corresponding flag variable to 1
					//if it is a p flag, read the next argument as well, which supplies the pid
						//increase the count
				//increase the count
				printf("this is a flag: %s\n", argv[count]);
				}
			else{
				//if it is not a flag, return an error
				printf("Entered an invalid flag: %s \n",argv[count]);
				printUsage();
				exit(1);
			}
			count++;
		}
	}
}
