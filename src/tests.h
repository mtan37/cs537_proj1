// Authors: Marvin Tan (marvin.tan@wisc.edu), Joseph Martin (jrmartin4@wisc.edu)

#ifndef TESTS_H
#define TESTS_H
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "processArgs.h"
#include "fileParser.h"
#include "userProcUtil.h"
//print out the value of the fields in the flags struct
void printFlagsVar(Flags *flagsVar);
void printStatInfo(StatInfo *statInfo);
void printStatInfoList(StatInfo **statInfoList, int listlength);
void printStatmInfoList(StatmInfo **statmInfoList, int listlength);
void printCmdlineInfoList(CmdInfo **cmdlineInfoList, int listlength);
void printCurrUserProcessList(int uid);
#endif
