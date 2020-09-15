#include "tests.h"
#include "processArgs.h"
#include <stdio.h>
void printFlagsVar(flags *flagsVar){
	//print out the flags
	printf("p flag is set to: %d\n", flagsVar->flag_p);
	printf("s flag is set to: %d\n", flagsVar->flag_s);
	printf("U flag is set to: %d\n", flagsVar->flag_U);
	printf("S flag is set to: %d\n", flagsVar->flag_S);
	printf("v flag is set to: %d\n", flagsVar->flag_v);
	printf("c flag is set to: %d\n", flagsVar->flag_c);
	//print out the length of the pid list
	printf("pid list length: %d\n", flagsVar->length_p);
	//loop through the pid list and print out the content
	for(int i=0; i < flagsVar->length_p; i++){
		if(flagsVar->length_p == 1){
			printf("Pid list:{%s}\n",flagsVar->content_p[i]);
		}
		else{
			if(i == 0)
				printf("Pid list:{%s,\n",flagsVar->content_p[i]);
			else if(i != (flagsVar->length_p-1))
				printf("	  %s,\n",flagsVar->content_p[i]);
			else
				printf("	  %s}\n",flagsVar->content_p[i]);
		}
	}
}

