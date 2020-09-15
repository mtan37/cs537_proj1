#include <stdlib.h>
#include <stdio.h>
#include "processArgs.h"

int main(int argc, char **argv){
	flags *flag_list = initFlags();
	//process the arguments
	processArguments(argc,argv);																	
}

