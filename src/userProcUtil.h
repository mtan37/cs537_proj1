// Authors: Marvin Tan (marvin.tan@wisc.edu), Joseph Martin (jrmartin4@wisc.edu)

#ifndef USERPROCUTIL_H
#define USERPROCUTIL_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "fileParser.h"
typedef struct ProcessNode {
	char *pid;
	struct ProcessNode *next;
} ProcessNode;
char *stringConcat(const char *string1, const char *string2);
FILE *fileOpener(const char *pid, int flag);
/*
 * This is a helper function to free the mem allocated for a linked process list
 * The function will only free the pid field in the ProcessNode struct only if 
 * the needFreePid field is set to 1
 */
void freeProcessList(ProcessNode *head, int needFreePid);
ProcessNode* getProcessesList(unsigned int uid);
#endif
