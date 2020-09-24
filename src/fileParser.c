// Authors: Marvin Tan (marvin.tan@wisc.edu), Joseph Martin (jrmartin4@wisc.edu)
#include "fileParser.h"
const int BUFFER_S = 100;

/**
 * Takes in the pid of a process, parse its stat file and store the values in
 * struct StatInfo and return a pointer to the struct
 * Return null if the process with pid doesn't exist
 */
StatInfo *statParser(const char *pid){
	StatInfo *statInfoVar = calloc(1,sizeof(StatInfo));
	statInfoVar->pid = pid;
    if(NULL == statInfoVar){
        printf("Error: Don't have enough memory for var allocation.\n");
        exit(1);        
    }
    char *buff = calloc(1,BUFFER_S);
    if(NULL == buff){
        printf("Error: Don't have enough memory for var allocation.\n");
        exit(1);        
    }
    FILE *file = fileOpener(pid,1);
    if(NULL == file){//the pid doesn't exist
        free(statInfoVar);
        free(buff);
        return NULL;
    }
    //continue read until get all the needed variable of end of the line
    char charTemp = '@';
    int i = 0;
    int flagFieldIndex = 0;//the index of the curr reading char array
    int getFlag_sFieldIndex = 2;//
    int getFlag_UFieldIndex = 13;
    int getFlag_SFieldIndex = 14;
    while (flagFieldIndex <= 14){
        charTemp =fgetc(file);
        //if reach file end before reading all the neccesary variables
        if(EOF == charTemp){
            printf("Error: corrupted stat file");
            exit(1);    
        }
        while(EOF != charTemp && ' ' != charTemp){
            buff[i] = charTemp;
            i++;
            charTemp =fgetc(file);
        }
        buff[i] = '\0';
        if (flagFieldIndex == getFlag_sFieldIndex){
            statInfoVar->flag_sField = calloc(1,sizeof(char) * i +1);
            if(NULL == statInfoVar->flag_sField){
                printf("Error: Don't have enough memory for var allocation.\n");
                exit(1);        
            }
            strncpy(statInfoVar->flag_sField,buff,i);
        }
        else if (flagFieldIndex == getFlag_UFieldIndex){
            statInfoVar->flag_UField = calloc(1,i+1);
            if(NULL == statInfoVar->flag_UField){
                printf("Error: Don't have enough memory for var allocation.\n");
                exit(1);        
            }
            strncpy(statInfoVar->flag_UField,buff,i+1);
        }
        else if(flagFieldIndex == getFlag_SFieldIndex){
            statInfoVar->flag_SField = calloc(1,i+1);
            if(NULL == statInfoVar->flag_SField){
                printf("Error: Don't have enough memory for var allocation.\n");
                exit(1);        
            }
            strncpy(statInfoVar->flag_SField,buff,i+1);
        }
        flagFieldIndex++;
        i = 0;
    }
    fclose(file);
    free(buff);
	return statInfoVar;
}

/**
 * Takes in the pid of a process, parse its statm file and store the values in
 * struct StatmInfo and return a pointer to the struct
 * Return null if the process with pid doesn't exist
 */
StatmInfo *statmParser(const char *pid){
	StatmInfo *statmInfoVar = calloc(1,sizeof(StatmInfo));
	if(NULL == statmInfoVar){
        printf("Error: Don't have enough memory for var allocation.\n");
        exit(1); 
    }
    char *buff = calloc(1,BUFFER_S);
	if(NULL == buff){
        printf("Error: Don't have enough memory for var allocation.\n");
        exit(1); 
    }
    FILE *file = fileOpener(pid,2);
    if(NULL == file){//the pid doesn't exist
        free(statmInfoVar);
        free(buff);
        return NULL;
    }
    //continue read until get all the needed variable of end of the line
    char charTemp = '@';
    int i = 0;
    int flagFieldIndex = 0;//the index of the curr reading char array
    int getFlag_vFieldIndex = 0;
    while (flagFieldIndex <= 0){
        charTemp =fgetc(file);
        //if reach file end before reading all the neccesary variables
        if(EOF == charTemp){
            printf("Error: corrupted statm file");
            exit(1);    
        }
        while(EOF != charTemp && ' ' != charTemp){
            buff[i] = charTemp;
            i++;
            charTemp =fgetc(file);
        }
        buff[i] = '\0';
        if (flagFieldIndex == getFlag_vFieldIndex){
            statmInfoVar->flag_vField = calloc(1,sizeof(char) * i +1);
            if(NULL == statmInfoVar->flag_vField){
                printf("Error: Don't have enough memory for var allocation.\n");
                exit(1); 
            }
            strncpy(statmInfoVar->flag_vField,buff,i);
        }
        flagFieldIndex++;
        i = 0;
    } 
	fclose(file);
    free(buff);
    return statmInfoVar;
}

/**
 * Takes in the pid of a process, parse the cmdline file and store the values in
 * struct CmdInfo and return a pointer to the struct
 * Return null if the process with pid doesn't exist
 */
CmdInfo *cmdlineParser(const char *pid){
	CmdInfo *cmdInfoVar = calloc(1,sizeof(CmdInfo));
	if(NULL == cmdInfoVar){
        printf("Error: Don't have enough memory for var allocation.\n");
        exit(1); 
    }
    char *buff = calloc(1,BUFFER_S);
	if(NULL == buff){
        printf("Error: Don't have enough memory for var allocation.\n");
        exit(1); 
    }
    FILE *file = fileOpener(pid,3);	
    if(NULL == file){//the pid doesn't exist
        free(cmdInfoVar);
        free(buff);
        return NULL;
    }
    char charTemp = '-';
    int i = 0;
    int run = 1;
    while(1 == run){
        charTemp = fgetc(file);
        while(0 != run && '\0' != charTemp && EOF != charTemp){
            buff[i] = charTemp;
            i++;
            charTemp = fgetc(file);
        }
        if(EOF == charTemp){//if it is the end
            //save string from the buff
            buff[i] = '\0';
            //initialize the char array and load in the command
            cmdInfoVar->flag_cField = calloc(i,sizeof(char)+1);
            if(NULL == cmdInfoVar->flag_cField){
                printf("Error: Don't have enough memory for var allocation.\n");
                exit(1); 
            }
            strncpy(cmdInfoVar->flag_cField,buff,i);
            run = 0;
            break;
        }
        else if('\0' == charTemp){//not the end, add space
            buff[i] = ' ';
        }
        else{//something is wrong if the code goes here...
            printf("Error: corrupted cmdline file for process pid: %s",pid);
            exit(1);
        }
    }
    free(buff);
	fclose(file);
    return cmdInfoVar;
}


