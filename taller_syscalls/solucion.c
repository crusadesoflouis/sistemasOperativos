#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


void imprimepadre (){
	write(1,"sup!\n",5);
}

void imprimehijo (){
	write(1,"ya va!\n",7);
}
void terminar(){
	exit(0);
}

int main (int argc, char* argv[]){
	int counter = 0;
	int pid = fork();

	while(counter < 5){
		if (pid == 0)
		{
			signal(SIGURG,imprimehijo);
			signal(SIGINT,terminar);
		}else{
			sleep(1);
			imprimepadre();
			if(counter < 5){
				kill(pid,SIGURG);
			}else{
				kill(pid,SIGINT);
			}
			counter = counter +1;
		}
	}
	//printf("%s\n", argv[1]);
	execvp(argv[1], argv+1);
	return 0;
}
