#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


void imprimeAbraham (){
	write(1,"Abraham\n",8);
}

void imprimeLisa (){
	write(1,"Lisa\n",5);
}

void imprimeBart (){
	write(1,"Bart\n",5);
}

void imprimeHomer (){
	write(1,"Homer\n",6);
}
void imprimeMaggie (){
	write(1,"Maggie\n",7);
}

int main (int argc, char* argv[]){
	int pidForAbraham = fork ();
	if (pidForAbraham != 0) {
		imprimeAbraham();
	}
	else{
		int pidForLisa = fork();
		if (pidForLisa == 0) {
			imprimeLisa();
		}
		else{
			int pidForBart = fork();
			if (pidForBart == 0) {
				imprimeBart();
			}
			else{
					int pidForMaggie = fork();
					if (pidForMaggie == 0) {
						imprimeMaggie();
					}
					else{
						imprimeHomer();
					}
			}
		}
	}

	return 0;
}
