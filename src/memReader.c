// Authors: Marvin Tan (marvin.tan@wisc.edu), Joseph Martin (jrmartin4@wisc.edu)

#include "memReader.h"
int isMemAddrInRange(FILE *file, unsigned long addr, long n){
    size_t bufSize = 64;
    char *buff = (char *)calloc(1,bufSize);
    char *tmpPtr;
    ssize_t returnV = getline(&buff,&bufSize,file);
    char *startAddr_s;
    char *endAddr_s;
    unsigned long startAddr;
    unsigned long endAddr;
    while(returnV != -1 || returnV != EOF){
        tmpPtr = strtok(buff," ");
        if('\0' == *tmpPtr){
            free(buff);
            return 0;
        }
        startAddr_s = strtok(tmpPtr,"-");
        endAddr_s = strtok(NULL,"-");
        startAddr = strtol(startAddr_s,&tmpPtr, 16);    
        if('\0' != *tmpPtr){//if the addr is converted incorrectly
            free(buff);
            return 0;    
        }
        endAddr = strtol(endAddr_s,&tmpPtr,16);    
        //if this starting address is in the range
        if((addr < endAddr && addr > startAddr)|| addr == startAddr
            || addr == endAddr){
            //check if the length is in bound
            if((n-1) <= (endAddr - addr)){
                free(buff);
                return 1;
            }
        }
        returnV = getline(&buff,&bufSize,file);
    }
    free(buff);
    return 0;
}

/*
 * Read n byte of mem info starting at address addr, 
 * Assuming the pass in argu * -ment has valid format
 * Return NULL if the memory is not mapped
 */
unsigned char *readMem(const char *pid, unsigned long addr, long n){
    //first verify whether the given addr range is mapped
    FILE *mapsFile = fileOpener(pid,4);
    if(NULL != mapsFile && 1 == isMemAddrInRange(mapsFile,addr,n)){ 
        FILE *memFile = fileOpener(pid, 5);
        //reposition the file stream to the starting addr
        fseeko(memFile,addr,SEEK_SET); 
        unsigned char *memContent = calloc(1,n+1);
        fread(memContent, sizeof(unsigned char) , n, memFile);
        memContent[n] = '\0';
        //close the mem file and maps file
        fclose(memFile);
        fclose(mapsFile);
        //detach from the process
        ptrace(PTRACE_DETACH,pid,0,0);
        return memContent;
    }    
    fclose(mapsFile);
    return NULL;
}

