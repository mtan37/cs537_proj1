#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "fileParser.h"
const int BUFFER_S = 50;

StatInfo *statParser(const char *pid){
	StatInfo *statInfoVar = calloc(1,sizeof(StatInfo));
	statInfoVar->pid = pid;
    //TODO ERROR HANDLER for all calloc and malloc
	//TODO Add free() to all allocated heap variables
    char *buff = calloc(1,BUFFER_S);
    FILE *file = fileOpener(pid,1);
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
            printf("index 2 executed\n");
            statInfoVar->flag_sField = calloc(i,sizeof(char));
            strncpy(statInfoVar->flag_sField,buff,i);
            printf("buffer field: %s; s flag field: %s\n", buff, statInfoVar->flag_sField);
        }
        else if (flagFieldIndex == getFlag_UFieldIndex){
            printf("index 13 executed\n");
            statInfoVar->flag_UField = calloc(1,i);
            strncpy(statInfoVar->flag_UField,buff,i);
        }
        else if(flagFieldIndex == getFlag_SFieldIndex){
            printf("index 14 executed\n");
            statInfoVar->flag_SField = calloc(1,i);
            strncpy(statInfoVar->flag_SField,buff,i);
        }
        flagFieldIndex++;
        i = 0;
    }
    fclose(file);
    free(buff);
	return statInfoVar;
}

StatmInfo *statmParser(const char *pid){
	StatmInfo *statmInfoVar = calloc(1,sizeof(StatmInfo));
	char *buff = calloc(1,BUFFER_S);
    FILE *file = fileOpener(pid,2);
    printf("statmParser check point #1111\n");//DELETE
    //continue read until get all the needed variable of end of the line
    char charTemp = '@';
    int i = 0;
    int flagFieldIndex = 0;//the index of the curr reading char array
    int getFlag_vFieldIndex = 0;
    while (flagFieldIndex <= 0){
        printf("statmParser check point #2222\n");//DELETE
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
            statmInfoVar->flag_vField = calloc(i,sizeof(char));
            strncpy(statmInfoVar->flag_vField,buff,i);
            printf("buffer field: %s; s flag field: %s\n", buff, statmInfoVar->flag_vField);
        }
        flagFieldIndex++;
        i = 0;
    } 
    printf("statmParser check point #3333\n");//DELETE
	fclose(file);
    free(buff);
    return statmInfoVar;
}

CmdInfo *cmdlineParser(const char *pid){
	CmdInfo *cmdInfoVar = calloc(1,sizeof(CmdInfo));
    char *buff = calloc(1,BUFFER_S);
    FILE *file = fileOpener(pid,3);	
    char charTemp = '-';
    int i = 0;
    int run = 1;
    printf("cmdline check point #1111\n");//DELETE
    while(1 == run){
        charTemp = fgetc(file);
        while(0 != run && '\0' != charTemp && EOF != charTemp){
            printf("charTemp: %c at i = %d\n",charTemp,i);
            buff[i] = charTemp;
            i++;
            charTemp = fgetc(file);
        }
        if(EOF == charTemp){//if it is the end
            //save string from the buff
            buff[i] = '\0';
            //initialize the char array and load in the command
            cmdInfoVar->flag_cField = calloc(i,sizeof(char));
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
    printf("cmdline check point #2222\n");//DELETE
    return cmdInfoVar;
}


