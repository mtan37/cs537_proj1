#ifndef PARSER_H
#define PARSER_H
//parse stat and statm files to extract strings from the list

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

StatInfo *statParser(const char *pid);
StatmInfo *statmParser(const char *pid);
CmdInfo *cmdlineParser(const char *pid);
#endif
