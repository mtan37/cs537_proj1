// Authors: Marvin Tan (marvin.tan@wisc.edu), Joseph Martin (jrmartin4@wisc.edu)

#ifndef OUTPUTGENERATOR_H
#define OUTPUTGENERATOR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "processArgs.h"
#include "userProcUtil.h"
#include "fileParser.h"
#include "memReader.h"

/*
 * Generates the output based on given flags 
 */
void generateOutput(Flags *flags, int uid);
#endif
