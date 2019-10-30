/*
 ============================================================================
 Name        : probando_cliente.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <readline/readline.h>
#include <readline/history.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>

int crear_conexion(char *ip, char* puerto){
	struct addrinfo hints;
	struct addrinfo *server_info;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	getaddrinfo(ip, puerto, &hints, &server_info);
	int socket_cliente = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
	if(connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1){
		perror("error en crear conexion");
		return -1;
	}
//		printf("error");
	freeaddrinfo(server_info);
	return socket_cliente;
}
int main(void) {
//	struct sockaddr_in direccionServer;
//	direccionServer.sin_family=AF_INET;
//	direccionServer.sin_addr.s_addr=INADDR_ANY;
//	direccionServer.sin_port=htons(8080);
//	int socket_cliente=socket(AF_INET,SOCK_STREAM,0);
//	if (connect(socket_cliente,(void*)&direccionServer,sizeof(direccionServer))!=0) {
//		perror("No se pudo conectar ");
//		return 1 ;
//	}
	int socket_cliente = crear_conexion("127.0.0.1","4445");
	if(socket_cliente==-1)return EXIT_FAILURE;
	for (;;) {

		char* mensaje=readline("-> ");
		int size_del_mensaje = strlen(mensaje);
		send(socket_cliente,&size_del_mensaje,sizeof(int),0);
		send(socket_cliente,mensaje,strlen(mensaje),0);
	}
	return EXIT_SUCCESS;
}
