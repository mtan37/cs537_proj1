#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "processArgs.h"
const int MAX_PID_LIST_SIZE = 20;
/**
 * Can now candle basic argument with the correct format
 * TODO: multiple occurance of -p, which should raise an error
 * TODO: the use of false flags such as -s-, -U-, -S-, -v- and -c-
 *
 **/


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
	flagsVar->content_p_size = 20;//default size 20
	flagsVar->content_p = calloc(flagsVar->content_p_size, sizeof(char*));
	return flagsVar;
}


/**
 * Check whether a pid is valid numeric string
 * If valid, return the length of the pid string. If not valid, return 0
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
int isFlagFormatValid(char *flag){
	//is the flag the right length?
	if(strlen(flag) == 2){
		return 1;
	}	
	return 0;
}

/**
 * Set the flags to default value if they are not already set by users
 */
void setFlagsToDefault(flags *flagsVar){
	//check p flag(default false)
	if(flagsVar->flag_p == -1)
		flagsVar->flag_p = 0;
	//check s flag(default false)
	if(flagsVar->flag_s == -1)
		flagsVar->flag_s = 0;
	//check U flag(default true)
	if(flagsVar->flag_U == -1)
		flagsVar->flag_U = 1;
	//check S flag(default false)
	if(flagsVar->flag_S == -1)
		flagsVar->flag_S = 0;
	//check v flag(default false)
	if(flagsVar->flag_v == -1)
		flagsVar->flag_v = 0;
	//check c flag(default true)
	if(flagsVar->flag_c == -1)
		flagsVar->flag_c = 1;
}

/**
 * Print usage to console
 */
void printUsage(){
}
/**
 * add new pid to the pid list in the flag struct
 */
void addPidToList(flags *flagsVar, char *pid){
	//check if the addition will exceed the size limit of the list
	if(flagsVar->length_p >= MAX_PID_LIST_SIZE){
		printf("Can't add more pid. Process pid: %s's information will not be displayed\n", pid);
		return;
	}
	if(isPidValid(pid)){
		(flagsVar->length_p)++;
		//add the pid to the list
		(flagsVar->content_p)[(flagsVar->length_p)-1]=pid;		
	}
	else{
		printf("Invalid pid format: %s \n",pid);
		printUsage();
		exit(1);
	}	
}
void processArguments(int argc,char **argv, flags *flagsVar){
  	//check if the count of argument is valid
	if(argc > 0){
		int count = 1;//start from index 1
		while(count < argc){
			//check to see if it is a flag(start with -?)
			if(argv[count][0]=='-'){
				//check if the flag is valid
				if(!isFlagFormatValid(argv[count])){
					printf("Invalid flag format: %s \n",argv[count]);
                	printUsage();
                	exit(1);
				}
				//process the flag arg
				//swith the corresponding flag variable to 1
				char flagType = argv[count][1];
				switch(flagType){
					case 'p':
						//switch the flag var
						flagsVar->flag_p = 1;
						//increase the count
						count++;
						//read the next argument as well, which supplies the pid
						addPidToList(flagsVar, argv[count]);
						break;
					case 's':
						//switch the flag var
						flagsVar->flag_s = 1;
						break;
					case 'U':
						//switch the flag var
						flagsVar->flag_U = 1;
						break;
					case 'S':
						//switch the flag var
						flagsVar->flag_S = 1;
						break;
					case 'v':
						//switch the flag var
						flagsVar->flag_v = 1;
						break;
					case 'c':
						//switch the flag var
						flagsVar->flag_c = 1;
						break;
					default:
						printf("flag type %s doesn exist \n",argv[count]);
						printUsage();
						exit(1);
				}
				//increase the count
				count++;
				}
			else{
				//if it is not a flag, return an error
				printf("Entered an invalid argument: %s \n",argv[count]);
				printUsage();
				exit(1);
			}
		}
		//check if there any flags not set by the user, and set them to default value
		setFlagsToDefault(flagsVar);		
	}
}
