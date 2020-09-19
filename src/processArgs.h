#ifndef PROCESSARGS_H
#define PROCESSARGS_H

typedef struct Flags{
    int flag_p;//specifies the pid of the process that needs to be displayed. If not present, this value will default to false, and program will print all process owned by the current user
    int flag_s;//display single-character state info about the process. If not present, default to false
    int flag_U;//Display the amount of user time consumed by the process. If not present, default to true
    int flag_S;//Display the amount of sytem time consumed by the process. If not present, default to false
    int flag_v;//Display the amount of virtual memory currently being used (in pages) by this program. If not present,default to false
    int flag_c;//Display the command-line that started the process. Default to true
    int length_p;
    char **content_p;
    int content_p_size;//the allocated size of content_p
}Flags;
/**
 * initalize flag variable to the following state:
 * int flag_p = -1;
 * int flag_s = -1;
 * int flag_U = -1;
 * int flag_S = -1;
 * int flag_v = -1;
 * int flag_c = -1;
 * int length_p = 0;
 */
Flags *initFlags();
void processArguments(int argc,char **arg,Flags *flagsVar);
#endif
