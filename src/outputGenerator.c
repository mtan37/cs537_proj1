#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "processArgs.h"
#include "userProcUtil.h"
#include "fileParser.h"

void generateOutput(Flags flags) {

    if (1 == flags->flag_p) { //p flag is present
	//TODO: use flags->content_p
	
    } else { // p flag is not present
	//use the process from getProcessesList(uid)
        uid = getuid();
	head = getProcessesList(uid);
    }
	
	
	
	
    for (int i = 0; i < flags->length_p; i++) {
        printf("%d: ",pid); //print out the pid of the process
        printf(' ');

        if (1 == flags->flag_s || 1 == flags->flag_U || 1 == flags->flag_S) {
            StatInfo statInfoVar = *statParser(*pid);
            if (1 == flags->flag_s) {
                printf("%s", statInfoVar->*flag_sField);
                printf(' ');
	    }
	    if (1 == flags->flag_U) {
                printf("%s", statInfoVar->*flag_sField);
                printf(' ');
	    }
	    if (1 == flags->flag_S) {
                printf("%s", statInfoVar->*flag_sField);
                printf(' ');
	    }
        }

        if (1 == flags->flag_v) {
            StatmInfo statmInfoVar = *statmParser(*pid);
            printf("%s", statmInfoVar->flag_vField);
            printf(' ');
        }

        if (1 == flags->flag_c) {
            CmdInfo cmdInfoVar = *cmdlineParser(*pid);
            printf("%s", cmdInfoVar->flag_cField);
        }

        printf("\n");
	head = (*head)->next;
    }
}

void printGeneratedOutput() {
    //create flags variable here and call processArguments(argc, **argv, flags)
    Flags flags = initFlags();
    processArguments(argc, **argv, flags);
	
    //print out header
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
    printf("\n");
	
    //generate the output by passing flags variable
    generateOutput(flags);
}
