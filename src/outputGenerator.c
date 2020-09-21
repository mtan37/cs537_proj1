#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "processArgs.h"
#include "userProcUtil.h"
#include "fileParser.h"

// Initialize output as char array
char output[1] = {'\0'};

// get head here from userProcUtil.c
// get statInfoVar here from fileParser.c statParser method
// get statmInfoVar here from fileParser.c statmParser method
// get cmdInfoVar here from fileParser.c cmdlineParser method

void generateOutput(Flags flags) {

    if (sizeof(flags) < 9) {
        // TODO: error message
        return NULL;
    }

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
        strcat(output, statInfoVar->flag_UField);
	strcat(output, ' ');
    }

    // Adds system time consumed to output if S flag is set in command line
    if (flags->flag_S == 1) {
        strcat(output, statInfoVar->flagSField);
	strcat(output, ' ');
    }

    // Adds amount of virtual memory currently being used (in pages) by the program to output if v flag is set in command line
    if (flags->flag_v == 1) {
        strcat(output, statmInfoVar->flag_vField);
	strcat(output, ' ');
    }

    // Adds command line info that started the program to output if c flag is set in command line
    if (flags->flag_c == 1) {
       strcat(output, '[');
       strcat(output, cmdInfoVar->flag_cField);
       strcat(output, ']');
    }
    
    // print output here
    printf("%s", output);
    free(output);
    output = NULL;
}
