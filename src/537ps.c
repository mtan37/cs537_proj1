#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "processArgs.h"
#include "fileParser.h"
#include "userProcUtil.h"
#include "tests.h"

const int debugg = 1;
int main(int argc, char **argv){
    //Flags *flagsVar = initFlags();
    //process the arguments
    //processArguments(argc,argv,flagsVar);
    /*if(flagsVar->flag_p ==1){
        StatInfo **statInfoList = calloc(flagsVar->length_p,sizeof(void*));
        for(int i = 0; i< (flagsVar->length_p); i++){        
            const char *pid = (flagsVar->content_p)[i];
            printf("read pid before give to parser: %s\n", pid); 
            StatInfo *statInfo = statParser(pid);
            statInfoList[i] = statInfo;
        }
    }*/
    if(debugg){
        printf("debug section\n");
        //printFlagsVar(flagsVar);
        //printStatInfoList(statInfoList, flagsVar->length_p);
        int uid = getuid();
        printCurrUserProcessList(uid);
    }
}

