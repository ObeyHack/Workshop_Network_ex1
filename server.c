#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <stdbool.h>
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

#define SERVER_PORT 7777
#define MEGABIT 1024
#define MSG_COUNT 1000

int warmup(int client_socket, int size_of_packet) {
    char message[MEGABIT];
    for (int i = 0; i < 1000; i++) {
        recv(client_socket, &message, size_of_packet, 0);
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


void receive_data(int client_socket, int size){
    char packet[MEGABIT] = {0};
    char recive[MEGABIT] = {0};
    warmup(client_socket, size);

    for (int j = 0; j < MSG_COUNT; j++) {
        recv(client_socket, packet, size, 0);
        //printf("Received %d bytes %d\n", i, j);
    }
    //send the reply
    send(client_socket, recive, size, 0);
}


int main()
{
    printf("Running server...");
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

    //listen for connections
    listen(server_socket, 1);
    //accept the connection
    int client_socket = accept(server_socket, NULL, NULL);


    for (int i = 1; i < MEGABIT; i=i*2) {
        //printf("Sending %d bytes\n", i);
        receive_data(client_socket, i);
    }
    return 0;

}
