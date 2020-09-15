#include <stdlib.h>
#include <stdio.h>
#include "processArgs.h"
#include "tests.h"
const int debugg = 1;
int main(int argc, char **argv){
	flags *flagsVar = initFlags();
	//process the arguments
	processArguments(argc,argv,flagsVar);
	if(debugg){
		printFlagsVar(flagsVar);
	}																	
}

