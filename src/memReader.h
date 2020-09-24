// Authors: Marvin Tan (marvin.tan@wisc.edu), Joseph Martin (jrmartin4@wisc.edu)

#ifndef MEMREADER_H
#define MEMREADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include "userProcUtil.h"
/*
 * Read n byte of mem info starting at address addr, 
 * Assuming the pass in argu * -ment has valid format
 * Return NULL if the memory is not mapped
 */
unsigned char *readMem(const char *pid, unsigned long addr, long n);
#endif
