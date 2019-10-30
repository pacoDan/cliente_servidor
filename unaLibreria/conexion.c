/*
 * conexion.c
 *
 *  Created on: 30 oct. 2019
 *      Author: utnso
 */
#include "conexion.h"

void loggear(){
	puts("Hola !!");
}

int  enviar_contenido(void* contenido,uint32_t bytes_a_enviar, int receptor){
	int enviados= send(receptor,&bytes_a_enviar,sizeof(uint32_t),0);
	if(enviados<0)perror("Error al enviar el size del contenido.");
	enviados=send(receptor,contenido,bytes_a_enviar,0);
	return enviados;
}
void* recibir_contenido(int emisor){
	void* buffer =NULL;
			int size_mensaje=-1;
			int bytesRecibidos=recv(emisor,&size_mensaje,sizeof(uint32_t),0);
			if(bytesRecibidos<0 || size_mensaje==-1){
				perror("error al recibir size del mensaje o se desconecto");
				return NULL;
			}
			buffer=malloc(size_mensaje);
			bytesRecibidos=recv(emisor,buffer,size_mensaje,0);
			if (bytesRecibidos<0)perror("Nada recibido");
			if(bytesRecibidos==0)perror("mensaje recibido vacio");
//			buffer[bytesRecibidos]='\0';
			printf("Llegaron %d bytes como  : %s y longitud %d \n",bytesRecibidos,buffer,size_mensaje);
			return buffer;
}
