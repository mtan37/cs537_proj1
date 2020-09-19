#ifndef PROCESSES_H
#define PROCESSES_H

typedef struct processNode {
	char* pid;
	struct processNode* next;
} processNode;
processNode* getProcessesList();
int getProcess(char*);

#endif
