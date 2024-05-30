#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <stdbool.h>
#include <unistd.h>

#define SERVER_PORT 7777
#define MEGABIT 1024
#define MSG_COUNT 1000

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
int warmup(int client_socket, int sizeofpacket) {
    char message[MEGABIT];
    for (int i = 0; i < 1000; i++) {
        send(client_socket, &message, sizeofpacket, 0);
    }
    return 0;
}


bool connect_to_server(int client_socket, char* ip) {
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = inet_addr(ip);
    int connection_status = connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if (connection_status != -1) {
        printf("Connected to server\n");
        return true;
    }
    return false;
}


double send_data(int client_socket, int size){
    struct timeval start, end;
    char packet[MEGABIT] = {0};
    char recive[MEGABIT] = {0};


    warmup(client_socket, size);
    gettimeofday(&start, NULL);
    for (int j = 0; j < MSG_COUNT; j++) {
        send(client_socket, packet, size, 0);
    }
    //receive the reply
    recv(client_socket, recive, size, 0);
    gettimeofday(&end, NULL);
    //calc troughput
    long total_time = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
    double troughput = ((double) MSG_COUNT * size) /(double)total_time;
    return troughput;
}


int main(int argc, char *argv[]) {
    printf("Running client...");
    char* ip = argv[1];

    // create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        printf("Error creating socket\n");
        exit(1);
    }

    if (!connect_to_server(client_socket, ip)) {
        printf("Error connecting to server\n");
        exit(1);
    }

    //send message to sever
    double troughputs[MEGABIT] = {0};
    for (int i = 1; i < MEGABIT; i=i*2) {
        //printf("Sending %d bytes\n", i);
        troughputs[i] = send_data(client_socket, i);
        printf("\nTroughput for %d bytes is %f\n", i, troughputs[i]);
    }

    close(client_socket);
    return 0;
}