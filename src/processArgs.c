#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "processArgs.h"
const int MAX_PID_LIST_SIZE = 20;

/**
 *  Initialize flags
 */
Flags *initFlags(){
    Flags *flagsVar = calloc(1, sizeof(Flags));
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
    while (pid[pidLength]!='\0'){
        //if is not a digit...
        if(!isdigit(pid[pidLength])){
            return 0;
        }
        //if the first digit is 0....
        if(0 == pidLength && 0 == isdigit(pid[pidLength])){
            printf("Error: pid can't start with 0\n");
            return 0;
        }
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
 * If valid, return the option type. If not valid, return 0
 * option type: 1 == flag set option to true. 2 = flag set option to false
 */
int isFlagFormatValid(char *flag){
    printf("flag letter: %c\n",flag[1]);//DELETE
    //is the flag the right length?
    if(2 == strlen(flag)){
        return 1;
    }
    //check if it is a p flag in the format 537ps -p<pid>
    else if(strlen(flag) > 2 && 'p' == flag[1]){
        return 1;
    }
    else if (3 == strlen(flag)){
        //check if it ends with '-'
        if(flag[2] == '-'){
            return 2;
        }
    }
    return 0;
}

/**
 * Set the flags to default value if they are not already set by users
 */
void setFlagsToDefault(Flags *flagsVar){
    //check p flag(defalt false)
    if(-1 == flagsVar->flag_p)
        flagsVar->flag_p = 0;
    //check s flag(default false)
    if(-1 == flagsVar->flag_s)
        flagsVar->flag_s = 0;
    //check U flag(default true)
    if(-1 == flagsVar->flag_U)
        flagsVar->flag_U = 1;
    //check S flag(default false)
    if(-1 == flagsVar->flag_S)
        flagsVar->flag_S = 0;
    //check v flag(default false)
    if(-1 == flagsVar->flag_v)
        flagsVar->flag_v = 0;
    //check c flag(default true)
    if(-1 == flagsVar->flag_c)
        flagsVar->flag_c = 1;
}

/**
 * Print usage to console
 */
void printUsage(){
    printf("Usage: ");
    printf("537ps [options]\n");
    printf("    options:\n");
    printf("    -p <pid> or -p<pid> Display process information with selected pid.\n");
    printf("    -s Display the single-character state information about the process.\n");
    printf("    -s- turns the -s option off\n");
    printf("    -U Display the amount of user time consumed by this process.\n");
    printf("    -U- turns the -U option off\n");
    printf("    -S Display the amount of system time consumed so far by this process.\n");
    printf("    -S- turns the -S option off\n");
    printf("    -v Display the amount of memory currently being used by this program.\n");
    printf("    -v- turns the -v option off\n");
    printf("    -c Display the command-line that started this program.\n");
    printf("    -c- turns the -c option off\n");
}
/**
 * add new pid to the pid list in the flag struct
 */
void addPidToList(Flags *flagsVar, char *pid){
    //check if the addition will exceed the size limit of the list
    if(flagsVar->length_p >= MAX_PID_LIST_SIZE){
        printf("Warning: Exceeds pid store list size limit. Process pid %s's information will not be displayed\n", pid);
        return;
    }
    if(isPidValid(pid)){
        (flagsVar->length_p)++;
        //add the pid to the list
        (flagsVar->content_p)[(flagsVar->length_p)-1]=pid;      
    }
    else{
        printf("Error: Invalid pid format: %s \n",pid);
        printUsage();
        exit(1);
    }   
}
void processArguments(int argc,char **argv, Flags *flagsVar){
    //check if the count of argument is valid
    if(argc > 0){
        int count = 1;//start from index 1
        while(count < argc){
            //check to see if it is a flag(start with -?)
            if('-' == argv[count][0]){
                //check if the flag is valid
                int flagLength = isFlagFormatValid(argv[count]);
                int isSetTrueFlag = 1;
                printf("flagLength: %d\n",flagLength);//DELETE
                if(1 == flagLength){
                    isSetTrueFlag = 1;
                }
                else if (2 == flagLength){
                    isSetTrueFlag = 0;
                }
                else {
                    printf("Error: Invalid flag format: %s \n",argv[count]);
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
                        //check whether an argument parse is needed
                        if(strlen(argv[count]) > 2){
                            char *pid_p = (argv[count]+2);
                            addPidToList(flagsVar, pid_p);  
                        }
                        else{
                            //increase the count
                            count++;
                            //read the next argument as well, which supplies the pid
                            addPidToList(flagsVar, argv[count]);
                        }
                        break;
                    case 's':
                        //switch the flag var
                        flagsVar->flag_s = isSetTrueFlag;
                        break;
                    case 'U':
                        //switch the flag var
                        flagsVar->flag_U = isSetTrueFlag;
                        break;
                    case 'S':
                        //switch the flag var
                        flagsVar->flag_S = isSetTrueFlag;
                        break;
                    case 'v':
                        //switch the flag var
                        flagsVar->flag_v = isSetTrueFlag;
                        break;
                    case 'c':
                        //switch the flag var
                        flagsVar->flag_c = isSetTrueFlag;
                        break;
                    default:
                        printf("Error: Flag type %s doesn exist \n",argv[count]);
                        printUsage();
                        exit(1);
                }
                //increase the count
                count++;
            }
            else{
                //if it is not a flag, return an error
                printf("Error: Invalid argument: %s \n",argv[count]);
                printUsage();
                exit(1);
            }
        }
        //check if there any flags not set by the user, and set them to default value
        setFlagsToDefault(flagsVar);        
    }
}
