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
	char* pid;
	struct ProcessNode* next;
} ProcessNode;
char *stringConcat(const char *string1, const char *string2);
FILE *fileOpener(const char *pid, int flag);
ProcessNode* getProcessesList(unsigned int uid);
#endif
