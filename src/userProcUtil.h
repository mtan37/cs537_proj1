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
/*
 * Return a string that is a deep copy of the contatination of the string1+srting2
 */
char *stringConcat(const char *string1, const char *string2);
/*
 *  open a file under the /proc/<pid>/ directory.
 *  The file opened is based on the  *  flag given
 *  flag = 1: /proc/<pid>/stat
 *  flag = 2: /proc/<pid>/statm
 *  flag = 3: /proc/<pid>/cmdline
 *  Return null if the file pointed at the file path doesn't exist
 */
FILE *fileOpener(const char *pid, int flag);
/*
 * This is a helper function to free the mem allocated for a linked process list
 * The function will only free the pid field in the ProcessNode struct only if 
 * the needFreePid field is set to 1
 */
void freeProcessList(ProcessNode *head, int needFreePid);
/*
 * Return the head of a linked list of all the processes owned by the uid
 */
ProcessNode* getProcessesList(unsigned int uid);
#endif
