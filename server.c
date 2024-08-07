#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <unistd.h>
//What do you need to measure?
//You need to measure throughput between two machines, for exponential series of message sizes,
//ranging from 1 byte to 1MB. Throughput is the highest possible transmission rate with that message
//size.
//How to measure throughput?
//In order to measure throughput you need code both for a server and a client (try to make them share as
//much code as possible). You run your server first and the client second, the client connects to the server
//and sends X messages (you decide how many, and explain your decision in a comment inside the code),
//the server replies after all X have arrived, and the client calculates the throughput based on the time it
//all took (you can ignore the reply in your calculation)

#define SERVER_PORT 8253
#define MEGABIT 1048576
#define MSG_COUNT 1000
#define ITERATIONS 100


int warmup(int client_socket, size_t size_of_packet, char* buffer) {
    for (int i = 0; i < ITERATIONS; i++) {
        recv(client_socket, buffer, size_of_packet, MSG_WAITALL);
    }
    return 0;
}


bool bind_server(int server_socket) {
    //define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    //bind the socket to our specified IP and port
    if(bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) !=0)
    {
        return false;
    }
    return true;
}


void receive_data(int client_socket, size_t size, char* buffer){
    warmup(client_socket, size, buffer);
    for (long j = 0; j < MSG_COUNT; j++) {
        recv(client_socket, buffer, size, MSG_WAITALL);
    }

    //send the reply
    send(client_socket, buffer, 1, 0);
}


int main()
{
    printf("Running server...\n");
    //create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        printf("Error creating socket\n");
        exit(1);
    }

    if (!bind_server(server_socket)) {
        printf("Error binding socket\n");
        exit(1);
    }
    char* buffer = (char*) malloc(MEGABIT);
    if (buffer == NULL) {
        printf("Error allocating memory\n");
        exit(1);
    }

    //listen for connections
    listen(server_socket, 1);
    //accept the connection
    int client_socket = accept(server_socket, NULL, NULL);


    for (size_t i = 1; i <= MEGABIT; i=i*2) {
        //printf("Sending %d bytes\n", i);
        receive_data(client_socket, i, buffer);
    }

    // close
    free(buffer);
    close(client_socket);
    close(server_socket);
    printf("Server closed\n");
    return 0;

}
