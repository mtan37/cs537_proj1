#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "processArgs.h"
#include "userProcUtil.h"
#include "fileParser.h"

void generateOutput(Flags flags) {

    if (1 == flags->flag_p) { //p flag is present
	//use flags->content_p
	ProcessNode *head = flags->content_p[0];
    } else { // p flag is not present
	//use the process from getProcessesList(uid)
	ProcessNode *head = getProcessesList(uid);
    }

    for (int i = 0; i < flags->length_p; i++) { //do we need to change flags->length_p to something else if the p flag is not set?
        printf("%d: ",pid); //print out the pid of the process

	//gets all stat information and prints if set
        if (1 == flags->flag_s || 1 == flags->flag_U || 1 == flags->flag_S) {
            StatInfo statInfoVar = *statParser(*pid);
            if (1 == flags->flag_s) {
                printf("%s ", statInfoVar->*flag_sField);
	    }
	    if (1 == flags->flag_U) {
                printf("%s ", statInfoVar->*flag_sField);
	    }
	    if (1 == flags->flag_S) {
                printf("%s ", statInfoVar->*flag_sField);
	    }
        }

	//gets statm information if v flag is set
        if (1 == flags->flag_v) {
            StatmInfo statmInfoVar = *statmParser(*pid);
            printf("%s ", statmInfoVar->flag_vField);
        }

	//gets command line information if c flag is set
        if (1 == flags->flag_c) {
            CmdInfo cmdInfoVar = *cmdlineParser(*pid);
            printf("%s", cmdInfoVar->flag_cField);
        }

	//prints newline for end of a process's information
        printf("\n");
	head = (*head)->next; //goes to next process
    }
}

void printGeneratedOutput() {
    //create flags variable here and call processArguments(argc, **argv, flags)
    Flags flags = initFlags();
    processArguments(argc, **argv, flags);
	
    //print out header for proper process info
    if (1 == flags->flag_p) {
        printf("PID ");
    }
    if (1 == flags->flag_s) {
        printf("STATE ");
    }
    if (1 == flags->flag_U) {
        printf("USER TIME ");
    }
    if (1 == flags->flag_S) {
        printf("SYSTEM TIME ");
    }
    if (1 == flags->flag_v) {
        printf("VIRTUAL MEMORY ");
    }
    if (1 == flags->flag_c) {
        printf("CMD LINE ");
    }
    printf("\n"); //prints newline after header is printed
	
    //generate the output by passing flags variable
    generateOutput(flags);
}
