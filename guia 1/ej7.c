#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>



/*
a) tiki y taka  deberian ser variables en el espacio compartido
b) temp no necesita ser compartida

void taka_runner (){}
void tiki_taka() {}
	int tiki;
	int taka;
	share_mem(tiki);
	share_mem(taka);


	int takaProcess = fork();
	if (takaProcess == 0 ) {
			taka_runner();
	}
	else{
		tiki_taka();
}

*/

void imprimeMaggie (){
	write(1,"Maggie\n",7);
}


int main (int argc, char* argv[]){

	return 0;
}
