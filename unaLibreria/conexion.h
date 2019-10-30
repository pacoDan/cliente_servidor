/*
 * conexion.h
 *
 *  Created on: 30 oct. 2019
 *      Author: utnso
 */

#ifndef CONEXION_H_
#define CONEXION_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>

void loggear();
int enviar_contenido(void* contenido, uint32_t bytes_a_enviar,int receptor);
void* recibir_contenido(int emisor);
#endif /* CONEXION_H_ */
