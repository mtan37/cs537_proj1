#ifndef FILEPARSER_H
#define FILEPARSER_H
#include "userProcUtil.h"
typedef struct StatInfo{
	const char *pid;//pid of the process
	//variables parsed from stat file
	char *flag_sField;//state information about the process
	char *flag_UField;//amount of user time consumed by the process
	char *flag_SField;//amount of system time consumed by the process
} StatInfo;

typedef struct StatmInfo{
	const char *pid;
	char *flag_vField;//amount of virtual memory currently being used
} StatmInfo;

typedef struct CmdInfo{
	const char *pid;
	char *flag_cField;//the command-line that started this program
} CmdInfo;
/**
 * Takes in the pid of a process, parse its stat file and store the values in
 * struct StatInfo and return a pointer to the struct
 */
StatInfo *statParser(const char *pid);

/**
 * Takes in the pid of a process, parse its statm file and store the values in
 * struct StatmInfo and return a pointer to the struct
 */
StatmInfo *statmParser(const char *pid);

/**
 * Takes in the pid of a process, parse the cmdline file and store the values in
 * struct CmdInfo and return a pointer to the struct
 */
CmdInfo *cmdlineParser(const char *pid);
#endif