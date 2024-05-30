#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define SEVER_IP "10.0.2.15"
#define SERVER_PORT 7000
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

int main(int argc, char *argv[]) {
    printf("Running client...");
    //connect to server
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        printf("Error creating socket\n");
        return 1;
    }
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = inet_addr(SEVER_IP);
    int connection_status = connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    if (connection_status == -1) {
        printf("Error connecting to server\n");
        return 1;
    }
    //send 1000 warmup messages of 8 bytes
    //for (int i = 0; i < 1000; i++) {
    //    char message[8] = "aaaaaaaa";
    //    send(client_socket, message, sizeof(message), 0);
    //}
    //send message to sever
    char message[5] = "hello";
    send(client_socket, message, sizeof(message), 0);
    return 0;
}