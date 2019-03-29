#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "config.h"

readsocket(int s)
{
	char buf[1024];
	ssize_t r;

	r = recv(s, buf, sizeof(buf) - 1, 0);
	if (r == -1)
		perror("recv");
	/* cierre de conexión o error */
	if (r == 0 || r == -1)
		goto end;

	/* transforma en string de C */
	buf[r] = '\0';
	printf("[%d] < %s", s, buf);

end:
	return r;
}


int main(int argc, char **argv)
{
	char buf[MSGLEN + 1];
	struct sockaddr_in local, remote;

	//Ejemplo de dirección de internet (AF_INET) para el servidor donde indica que va a
	//a recibir paquetes de cualquier IP (INADDR_ANY) en el puerto PORT.
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(PORT);


	//TODO: Crear el socket
	int enchufe = socket(AF_INET,SOCK_STREAM,0);

	//TODO: Hacer el bind a la dirección de local
	int  conexion = bind(enchufe,(struct sockaddr_in *)&local,sizeof(local));
	//TODO: Completar conexión del socket para TCP (¿qué otros pasos hacen falta)
	if (listen(enchufe, 2) == -1) {
		perror("listen");
		exit(1);
	}


	int remotelen = sizeof(remote);
	int cfd0;
	if ((cfd0 = accept(enchufe, (struct sockaddr *)&remote, (socklen_t *)&remotelen))
	    == -1) {
		perror("accept cfd0");
		exit(1);
	}
	int lectura;

	while(1){
		memset(&buf, 0, MSGLEN+1);

		lectura = recv(enchufe, buf, sizeof(buf) - 1, 0);
		//Imprimir comando
		printf("comando: %s", buf);

		if (strncmp(buf, ENDMSG, sizeof(ENDMSG)) == 0)
			break;
		//Ejectuar comando
		if(system(buf) == -1){
			perror("error ejecución comando");
			break;
		}
	}
    //TODO: Cerrar el socket
		close(enchufe);
	return 0;
}
