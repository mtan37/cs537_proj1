#include <stdlib.h>
#include <stdio.h>

typedef struct flags{
	int flag_p = 0;//specifies the pid of the process that needs to be displayed. If not present, print all process owned by the current user
	int flag_s = 0;//display single-character state info about the process. If not present, default to false
	int flag_U = 0;//Display the amount of user time consumed by the process. If not present, default to true
	int flag_S = 0;//Display the amount of sytem time consumed by the process. If not present, default to false
	int flag_v = 0;//Display the amount of virtual memory currently being used (in pages) by this program.
	int flag_c = 0;//Display the command-line that started the process. Default to true
	char *content_p;
}
int main(int argc, char **argv){
	flags *flag_list = calloc(6, sizeof(flags));
																								
	free(flags);
}

int processArgument(char *arg){
	//check to see if it is a flag(start with -?)
		//if it is a flag, swith the corresponding flag variable to 1
	//else
}
