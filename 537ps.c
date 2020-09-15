#include <stdlib.h>
#include <stdio.h>
#include "processArgs.h"

int main(int argc, char **argv){
	flags *flag_list = calloc(1, sizeof(flags));
	//process the arguments
	processArguments(argc,argv);																		
	free(flags);
}

