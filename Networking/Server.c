#include  "Server.h"

struct Server server_constructor(int domain, int service, int protocol, unsigned long interface, int port, int backlog, void (*launch)(void))
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

    return server;
}

