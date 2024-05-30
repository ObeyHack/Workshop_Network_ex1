#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
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
#define SERVER_PORT 7005
#define SERVER_IP "10.0.2.15"
#define CLIENT_IP "0.0.0.0"
#define CLIENT_PORT 8081
#define MEGABIT 1024
int warmup(int client_socket, int sizeofpacket) {
    char message[MEGABIT];
    for (int i = 0; i < 1000; i++) {
        send(client_socket, &message, sizeofpacket, 0);
    }
    return 0;
}
int main()
{
    printf("Running server...");
    //create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        printf("Error creating socket\n");
        return 1;
    }
    //define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    //bind the socket to our specified IP and port
    if(bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) !=0)
    {
        printf("Error binding socket\n");
        return 1;
    }
    //listen for connections
    listen(server_socket, 5);
    //accept the connection
    int client_socket = accept(server_socket, NULL, NULL);
    //receive 1000 messages of 8 bytes as a warmup
    char message[8];



    int number_of_messages = 1000;

    char packet[MEGABIT] = {0};
    char recive[MEGABIT] = {0};

    for (int i = 1; i < MEGABIT; i=i*2) {
        warmup(client_socket, i);

        for (int j = 0; j < number_of_messages; j++) {
            recv(client_socket, packet, i, 0);
            //printf("Received %d bytes %d\n", i, j);
        }

        //send the reply
        send(client_socket, recive, i, 0);

    }
    return 0;

}
int main2()
{
    printf("Running server...");
    //create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        printf("Error creating socket\n");
        return 1;
    }
    //define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    //bind the socket to our specified IP and port
    if(bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) !=0)
    {
        printf("Error binding socket\n");
        return 1;
    }
    //listen for connections
    listen(server_socket, 5);
    //accept the connection
    int client_socket = accept(server_socket, NULL, NULL);
    //receive data from the client
    char message[5];
    recv(client_socket, &message, sizeof(message), 0);
    printf("Received: %s\n", message);
    return 0;
}