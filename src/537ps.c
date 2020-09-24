#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "processArgs.h"
#include "fileParser.h"
#include "userProcUtil.h"
#include "memReader.h"
#include "outputGenerator.h"
int main(int argc, char **argv){
    Flags *flagsVar = initFlags();
    //process the arguments
    processArguments(argc,argv,flagsVar);
    int uid = getuid();
    generateOutput(flagsVar, uid);     
    freeFlagsStruct(flagsVar);
    return 0;
}

