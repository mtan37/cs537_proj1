#ifndef TESTS_H
#define TESTS_H

#include "processArgs.h"
#include "parser.h"
//print out the value of the fields in the flags struct
void printFlagsVar(Flags *flagsVar);
void printStatInfo(StatInfo *statInfo);
void printStatInfoList(StatInfo **statInfoList, int listlength);
#endif
