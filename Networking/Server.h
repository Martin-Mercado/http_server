#ifndef Server_h
#define Server_h

#include <sys/socket.h>
#include <sys/types.h>

//contiene definiciones para protocolos
#include <netinet/in.h>
#include <newlib/sys/types.h>

struct Server
{
	int domain;
	int service;
	int protocol;
	unsigned long interface;
	int port;

	// largo maximo de fila de conecciones pendientes
	int backlog;

	struct sockaddr_in address;

	//puntero a una funcion launch, no devuelve nada ni lleva argumentos
	void (*launch)(void); 
};

//constructor de Server (prototipado)
struct Server server_constructor(int domain, int service, int protocol, unsigned long interface, int port, int backlog, void (*launch)(void));

#endif /* Server_h */

