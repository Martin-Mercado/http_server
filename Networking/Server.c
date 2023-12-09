#include  "Server.h"

#include  <stdio.h>
#include <stdlib.h>


struct Server server_constructor(int domain, int service, int protocol, unsigned long interface, int port, int backlog, void (*launch)(struct Server *server))
{
    struct Server server;
    
    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server.interface = interface;
    server.port = port;
    server.backlog = backlog;

    //crear la direccion
    server.address.sin_family = domain;
    //sin_family indica el tipo de direccion 

    server.address.sin_port = htons(port);
    //htons (host to network) convierte un int a un de orden de byte de host a orden de byte de red

    server.address.sin_addr.s_addr = htonl(interface);
    //htonl, mismo que htons pero para long

    server.socket = socket(domain, service, protocol);


    //test de socket
    if(server.socket == 0)
    {
        perror("no se pudo conectar al socket\n");
        exit(1);
    }
    
    //realizar el binding
    if(bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address)) < 0)
    {
        perror("No se pudo hacer el binding\n");
        exit(1);
    }

    if(listen(server.socket, server.backlog) < 0)
    {
        perror("Error al empezar el listening\n");
        exit(1);
    }

    //funcion de inicializacion
    server.launch = launch;

    return server;
}

