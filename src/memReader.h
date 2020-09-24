// Authors: Marvin Tan (marvin.tan@wisc.edu), Joseph Martin (jrmartin4@wisc.edu)

#ifndef MEMREADER_H
#define MEMREADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include "userProcUtil.h"
unsigned char *readMem(const char *pid, unsigned long addr, long n);
#endif
