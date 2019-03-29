#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define NELEMS(a) (sizeof(a) / sizeof((a)[0]))

static int run(const char ***progs, size_t count)
{

	//TODO: Guardar el PID de cada proceso hijo creado en children[i]
	pid_t *children;
	int i, status;
	i = 0;
	if (!(children = malloc(sizeof(*children) * count))) {
		fputs("out of memory\n", stderr);
		goto end;
	}

	//TODO: Pensar cuantos procesos necesito
	//TODO: Pensar cuantos pipes necesito.
		int pipefd[2];
		int pipefd2[2];
		pipe(pipefd);
		pipe(pipefd2);
		int pid = fork();
		if(pid == 0){
			//comando ls
			dup2(pipefd[1],1); // la salida de ls va a la entra del pipe de la tabla de descriptores
			close(pipefd[0]);
			close(pipefd2[1]);
			close(pipefd2[0]);
			execvp(progs[0][0],progs[0]);
		}
		children[i] = pid;
		i++;
		int pid2 = fork();
		if(pid2 == 0){
			dup2(pipefd[0],0); // la entrade de wc va leer la salida de ls por medio de la salida pipe 4
			dup2(pipefd2[1],1); // la salida de wc va ser la entrada del nuevo pipe
			close(pipefd[1]);
			close(pipefd2[0]);
			execvp(progs[1][0],progs[1]);
		}
		children[i] = pid2;
		i++;
		dup2(pipefd2[0],0);
		close(pipefd[0]);
		close(pipefd[1]);
		close(pipefd2[1]);
		execvp(progs[2][0],progs[2]);
		//codigo del padre


	//TODO: Para cada proceso hijo:
			//1. Redireccionar los file descriptors adecuados al proceso
			//2. Ejecutar el programa correspondiente

	//El padre espera a que terminen todos los procesos hijos que ejecutan los programas
	for (i = 0; i < count; i++) {
		if (waitpid(children[i], &status, 0) == -1) {
			perror("waitpid");
			return -1;
		}
		if (!WIFEXITED(status)) {
			fprintf(stderr, "proceso %d no terminó correctamente [%d]: ",
			    (int)children[i], WIFSIGNALED(status));
			perror("");
			return -1;
		}
	}

end:
	free(children);

	return 0;
}

int main(int argc, char **argv)
{
	char *lscmd[] = { "ls", "-al", NULL };
	char *wccmd[] = { "wc", NULL };
	char *awkcmd[] = { "awk", "{ print $2 }", NULL };
	char **progs[] = { lscmd, wccmd, awkcmd };

	printf("status: %d\n", run(progs, NELEMS(progs)));
	fflush(stdout);
	fflush(stderr);

	return 0;
}
