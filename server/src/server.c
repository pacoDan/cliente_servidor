/*
 ============================================================================
 Name        : probando_server.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>

#include <conexion.h>

int iniciar_servidor(const char* _SERVER_IP,const char* _SERVER_PUERTO){// parece ok
	int socket_servidor;
    struct addrinfo hints, *servinfo, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(_SERVER_IP, _SERVER_PUERTO, &hints, &servinfo);
    for (p=servinfo; p != NULL; p = p->ai_next)
    {
        if ((socket_servidor = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
            continue;
        if (bind(socket_servidor, p->ai_addr, p->ai_addrlen) == -1) {
        	perror("Fallo el bind");
        	close(socket_servidor);
            continue;
        }
        break;
    }
	listen(socket_servidor, SOMAXCONN);
    freeaddrinfo(servinfo);
    puts("inicia servidor");
    return socket_servidor;
}

int main(void) {
	loggear();
	int server = iniciar_servidor("127.0.0.1","4445");
	puts("Estoy escuchando");
	//-------------------------------------
	struct sockaddr_in direcionCliente;
	unsigned int tamanioDireccion;
	int cliente = accept(server,(void*)(&direcionCliente),&tamanioDireccion);
	printf("Recibi una conexion, fd de cliente es  %d !!\n",cliente);
	char mensaje[] = "Hola Cliente soy server",otroMensaje[]="como va";
//	send(cliente,mensaje,sizeof(mensaje),0);
//	send(cliente,otroMensaje,sizeof(otroMensaje),0);
	enviar_contenido(mensaje,sizeof(mensaje)+1,cliente);
//------------------------------------
	while(1){
//		char* buffer =NULL;
//		int size_mensaje=-1;
//		int bytesRecibidos=recv(cliente,&size_mensaje,sizeof(uint32_t),0);
//		if(bytesRecibidos<0 || size_mensaje==-1){
//			perror("error al recibir size del mensaje o se desconecto");
//			return EXIT_FAILURE;
//		}
//		buffer=malloc(size_mensaje);
//		bytesRecibidos=recv(cliente,buffer,size_mensaje,0);
//		if (bytesRecibidos<0)perror("Nada recibido");
//		if(bytesRecibidos==0)perror("mensaje recibido vacio");
////		buffer[bytesRecibidos]='\0';
//		printf("Llegaron %d bytes como  : %s y longitud %d \n",bytesRecibidos,buffer,size_mensaje);
//		free(buffer);

		char* carta = (void*)recibir_contenido(cliente);
		if(carta==NULL){
			perror("cliente se desconecto.");
			break;
		}
		free(carta);
	}
	return EXIT_SUCCESS;

}
