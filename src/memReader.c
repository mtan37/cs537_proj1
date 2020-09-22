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
            return 0;
        }
        startAddr_s = strtok(tmpPtr,"-");
        endAddr_s = strtok(NULL,"-");
        startAddr = strtol(startAddr_s,&tmpPtr, 16);    
        if('\0' != *tmpPtr){//if the addr is converted incorrectly
            return 0;    
        }
        endAddr = strtol(endAddr_s,&tmpPtr,16);    
        printf("input addr: %lx, start addr: %lx, end addr: %lx\n",addr,startAddr,endAddr);
        //if this starting address is in the range
        if((addr < endAddr && addr > startAddr)|| addr == startAddr
            || addr == endAddr){
            //check if the length is in bound
            if((n-1) <= (endAddr - addr)){
                return 1;
            }
        }
        returnV = getline(&buff,&bufSize,file);
    }
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
        printf("mem is in range\n");
        FILE *memFile = fileOpener(pid, 5);
        //reposition the file stream to the starting addr
        fseeko(memFile,addr,SEEK_SET); 
        unsigned char *memContent = calloc(1,n+1);
        fread(memContent, sizeof(unsigned char) , n, memFile);
        memContent[n] = '\0';
        //close the mem file
        fclose(memFile);
        //detach from the process
        ptrace(PTRACE_DETACH,pid,0,0);
        return memContent;
    }    
    return NULL;
}

