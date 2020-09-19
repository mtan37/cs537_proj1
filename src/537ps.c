#include <stdlib.h>
#include <stdio.h>
#include "processArgs.h"
#include "parser.h"
#include "tests.h"

const int debugg = 1;
int main(int argc, char **argv){
    Flags *flagsVar = initFlags();
    //process the arguments
    processArguments(argc,argv,flagsVar);
    StatInfo **statInfoList = calloc(flagsVar->length_p,sizeof(void*));
    for(int i = 0; i< (flagsVar->length_p); i++){        
        const char *pid = (flagsVar->content_p)[i];
        printf("read pid before give to parser: %s\n", pid); 
        StatInfo *statInfo = statParser(pid);
        statInfoList[i] = statInfo;
    }
    if(debugg){
        printFlagsVar(flagsVar);
        printStatInfoList(statInfoList, flagsVar->length_p);
    }
}

