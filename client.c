#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>


#define SEVER_IP2 "10.0.2.15"
#define SEVER_IP "132.65.164.101"
#define SERVER_PORT 7005
#define MEGABIT 1048576

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
    int connection_status = connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if (connection_status == -1) {
        printf("Error connecting to server\n");
        return 1;
    }

    //send message to sever
    struct timeval start, end;
    double troughputs[MEGABIT] = {0};
    int number_of_messages = 1000;




    gettimeofday(&start, NULL);
    char packet[MEGABIT] = {0};
    char recive[MEGABIT] = {0};

    for (int i = 1; i < MEGABIT; i=i*2) {
        //printf("Sending %d bytes\n", i);
        warmup(client_socket, i);
        gettimeofday(&start, NULL);
        for (int j = 0; j < number_of_messages; j++) {
            send(client_socket, packet, i, 0);
            //printf("sent %d bytes %d\n", i, j);
        }
        //receive the reply
        recv(client_socket, recive, i, 0);
        gettimeofday(&end, NULL);
        //calc troughput
        long mic = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
        long total_time = mic;
        double troughput = ((double) number_of_messages * i) /(double)total_time;
        troughputs[i] = troughput;
    }
    for (int i = 1; i < MEGABIT; i++) {
        printf("Troughput for %d bytes is %f\n", i, troughputs[i]);
    }


    return 0;
}