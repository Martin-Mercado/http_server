#include <stdio.h>
#include <string.h>
#include "Server.h"
#include <unistd.h>
#include "Server.c"

//definir funcion de inicializacion
void launch(struct Server *server)
{
    
    // Definir el buffer
    char buffer[30000];

    char *hello = "HTTP/1.1 200 OK\nGMT\nServer: Apache/2.2.14 (Win32)\nLast-Modified: Wed, 22,Jul 2009 19:15:56 GMT\nContent-Type: text/html\nConnection: Closed\n\n<html><body><h1>Working</h1></body></html>";

    int address_len = sizeof(server->address);
    int new_socket;

    while(1)
    {
        printf("==== ESPERANDO CONEXION ====\n");

        // Declarar nuevo socket
        new_socket = accept(server->socket,(struct sockaddr *)&server->address, (socklen_t *)&address_len);
        
      
        read(new_socket,buffer,30000);

        printf("%s\n", buffer);

        write(new_socket, hello,strlen(hello));

        close(new_socket);
    }
    
}

int main()
{
    printf("Entered Main\n");

    // puertos debajo de 1024 precisan de permisos elevados (socket 80 for http)
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80,10, launch);

    printf("Saliendo de constructor\n");
    server.launch(&server);
}