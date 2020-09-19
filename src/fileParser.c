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
    int flagFieldIndex = 0;
    int getFlag_sField = 2;
    int getFlag_UField = 13;
    int getFlag_SField = 14;
    while (flagFieldIndex <= 14){
        charTemp =fgetc(file);
        while(charTemp != EOF && charTemp != ' '){
            buff[i] = charTemp;
            i++;
            charTemp =fgetc(file);
        }
        buff[i] = '\0';
        if (flagFieldIndex == getFlag_sField){
            printf("index 2 executed\n");
            statInfoVar->flag_sField = calloc(i,sizeof(char));
            strncpy(statInfoVar->flag_sField,buff,i);
            printf("buffer field: %s; s flag field: %s\n", buff, statInfoVar->flag_sField);
        }
        else if (flagFieldIndex == getFlag_UField){
            printf("index 13 executed\n");
            statInfoVar->flag_UField = calloc(1,i);
            strncpy(statInfoVar->flag_UField,buff,i);
        }
        else if(flagFieldIndex == getFlag_SField){
            printf("index 14 executed\n");
            statInfoVar->flag_SField = calloc(1,i);
            strncpy(statInfoVar->flag_SField,buff,i);
        }
        flagFieldIndex++;
        i = 0;
    }
    //fread(buff,1,BUFFER_S,file);
    //printf("state of buffer: %s, length: %ld", buff,strlen(buff));
    fclose(file);
    free(buff);
	return statInfoVar;
}

StatmInfo *statmParser(const char *pid){
	StatmInfo *statmInfoVar = calloc(1,sizeof(StatmInfo));
	//TODO
	return statmInfoVar;
}

CmdInfo *cmdlineParser(const char *pid){
	CmdInfo *cmdInfoVar = calloc(1,sizeof(CmdInfo));
	//TODO
	return cmdInfoVar;
}


