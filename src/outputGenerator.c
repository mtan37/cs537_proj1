#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "processArgs.h"
#include "userProcUtil.h"
#include "fileParser.h"

void generateOutput(Flags flags) {

    // Adds all pid's to the output if p flag is set in command line
    if (flags->flag_p == 1) {
        ProcessNode *curr;
	if (head == NULL) {
            return;
        }
	curr = head;
	while (cur != NULL) {
            strcat(output, temp->pid);
	    strcat(output, ' ');
	    curr = curr->next;
        }
    }

    // Adds state to output if s flag is set in command line
    if (flags->flag_s == 1) {
        strcat(output, statInfoVar->flag_sField);
	strcat(output, ' ');
    }

    // Adds user time consumed to output if U flag is set in command line
    if (flags->flag_U == 1) {
        printf("%2", statInfoVar->flag_UField);
	printf(' ');
    }

    // Adds system time consumed to output if S flag is set in command line
    if (flags->flag_S == 1) {
	    //TODO: get statInfoVar
        printf("%s", statInfoVar->flagSField);
	printf(' ');
    }

    // Adds amount of virtual memory currently being used (in pages) by the program to output if v flag is set in command line
    if (flags->flag_v == 1) {
	    //TODO: Get statmInfoVar
        printf("%s", statmInfoVar->flag_vField);
	printf(' ');
    }

    // Adds command line info that started the program to output if c flag is set in command line
    if (flags->flag_c == 1) {
	    //TODO: Get cmdInfoVar
        printf("[");
        printf("%s", cmdInfoVar->flag_cField);
        printf("] ");
    }
	
    printf("\n");
}

void printGeneratedOutput() {
	
}
