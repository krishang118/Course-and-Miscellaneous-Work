#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>      
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 6000
#define BUFFER_SIZE 1024
#define WINDOW_SIZE 5
#define MAX_MESSAGES 20  
typedef struct {
    int message_id;
    char message[BUFFER_SIZE];
    int acked;
} Message;
int main() {
    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];
    int n;
    Message window[WINDOW_SIZE];
    int base = 0;         
    int next_seq = 0;     
    int total_sent = 0;
    int total_acked = 0;
    for (int i = 0; i < WINDOW_SIZE; i++) {
        window[i].message_id = -1; 
        memset(window[i].message, 0, BUFFER_SIZE);
        window[i].acked = 0;}
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(EXIT_FAILURE);}
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;                     
    serv_addr.sin_port = htons(PORT);             
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        close(sockfd);
        exit(EXIT_FAILURE);}
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        close(sockfd);
        exit(EXIT_FAILURE);}
    printf("Connected to server.\n");
    while (total_acked < MAX_MESSAGES) {
        while ((next_seq - total_acked) < WINDOW_SIZE && next_seq < MAX_MESSAGES) {
            snprintf(window[next_seq % WINDOW_SIZE].message, BUFFER_SIZE, "hello\n");
            window[next_seq % WINDOW_SIZE].message_id = next_seq;
            window[next_seq % WINDOW_SIZE].acked = 0;
            n = send(sockfd, window[next_seq % WINDOW_SIZE].message, strlen(window[next_seq % WINDOW_SIZE].message), 0);
            if (n < 0) {
                perror("Error writing to socket");
                close(sockfd);
                exit(EXIT_FAILURE);}
            total_sent++;
            printf("Sent message #%d: hello\n", next_seq + 1);
            next_seq++;}
        memset(buffer, 0, BUFFER_SIZE);
        n = recv(sockfd, buffer, BUFFER_SIZE - 1, 0);
        if (n < 0) {
            perror("Error reading from socket");
            break;}
        if (n == 0) {
            printf("Server closed connection unexpectedly.\n");
            break;}
        char *start_ptr = buffer;
        int bytes_in_buffer = n;
        while (bytes_in_buffer > 0) {
            char *newline_ptr = memchr(start_ptr, '\n', bytes_in_buffer);
            if (newline_ptr == NULL) {
                break;}
            int ack_length = newline_ptr - start_ptr;
            if (ack_length <= 0) {
                start_ptr = newline_ptr + 1;
                bytes_in_buffer -= (ack_length + 1);
                continue;}
            char ack_message[BUFFER_SIZE];
            strncpy(ack_message, start_ptr, ack_length);
            ack_message[ack_length] = '\0';
            printf("Received ACK: %s\n", ack_message);
            total_acked++;
            int acked_index = (total_acked - 1) % WINDOW_SIZE;
            if (window[acked_index].message_id == (total_acked - 1)) {
                window[acked_index].acked = 1;
                window[acked_index].message_id = -1;
                memset(window[acked_index].message, 0, BUFFER_SIZE);
            } else {
                printf("Warning: Received out-of-order ACK.\n");}
            start_ptr = newline_ptr + 1;
            bytes_in_buffer -= (ack_length + 1);}}
    snprintf(buffer, BUFFER_SIZE, "bye\n");
    n = send(sockfd, buffer, strlen(buffer), 0);
    if (n < 0) {
        perror("Error writing 'bye' to socket");}
    printf("Sent 'bye' to server.\n");
    close(sockfd);
    printf("Client closed.\n");
    return 0;}