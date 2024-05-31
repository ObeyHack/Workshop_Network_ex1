#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <stdbool.h>
#include <unistd.h>

#define SERVER_PORT 8123
#define MEGABIT 1048576
#define MEGA_POWER 20
#define MSG_COUNT 1000
#define ITERATIONS 1000

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
int warmup(int client_socket, size_t  size_of_packet, char* buffer) {
    for (int i = 0; i < ITERATIONS; i++) {
        send(client_socket, buffer, size_of_packet, 0);
    }
    return 0;
}


bool connect_to_server(int client_socket, char* ip) {
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = inet_addr(ip);
    int connection_status = connect(client_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    if (connection_status != -1) {
        printf("Connected to server\n");
        return true;
    }
    return false;
}


double send_data(int client_socket, size_t size, char* buffer) {
    struct timeval start, end;
    warmup(client_socket, size, buffer);
    gettimeofday(&start, NULL);
    for (int j = 0; j < MSG_COUNT; j++) {
        send(client_socket, buffer, size, 0);
    }

    recv(client_socket, buffer, size, 0);
    gettimeofday(&end, NULL);
    //calc throughput
    long total_time = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
    double throughput = ((double) MSG_COUNT * size) /(double)total_time;
    return throughput;
}


int main(int argc, char *argv[]) {
    printf("Running client...\n");
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

    char* buffer = (char*) malloc(MEGABIT);
    if (buffer == NULL) {
        printf("Error allocating memory\n");
        exit(1);
    }

    printf("Interval is %d\n\n", ITERATIONS);
    //send message to sever
    double* throughputs = (double*) malloc((MEGA_POWER+1) * sizeof(double));
    double avg_throughput = 0;
    int index = 0;
    for (size_t i = 1; i <= MEGABIT; i=i*2) {
        //printf("Sending %d bytes\n", i);
        throughputs[index] = send_data(client_socket, i, buffer);
        printf("Throughput for %lu bytes is %f\n", i, throughputs[index]);
        avg_throughput += throughputs[index];
        index++;
    }
    avg_throughput = avg_throughput / MEGA_POWER;
    printf("Average throughput is %f\n\n", avg_throughput);

    //close
    free(buffer);
    free(throughputs);
    close(client_socket);
    printf("Client closed\n");
    return 0;
}