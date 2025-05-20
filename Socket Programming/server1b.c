#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>      
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>     
#define PORT 6000
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 5
void *handle_client(void *socket_desc);
int main() {
    int sockfd, newsockfd;
    socklen_t client_len;
    struct sockaddr_in serv_addr, cli_addr;
    pthread_t thread_id;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(EXIT_FAILURE);}
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;             
    serv_addr.sin_addr.s_addr = INADDR_ANY;     
    serv_addr.sin_port = htons(PORT);          
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error on binding");
        close(sockfd);
        exit(EXIT_FAILURE);}
    listen(sockfd, MAX_CLIENTS);
    printf("Server listening.\n");
    while (1) {
        client_len = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &client_len);
        if (newsockfd < 0) {
            perror("Error on accept");
            continue;}
        printf("Client connected.\n");
        if (pthread_create(&thread_id, NULL, handle_client, (void *)&newsockfd) < 0) {
            perror("Could not create thread");
            close(newsockfd);
            continue;}
        pthread_detach(thread_id);}
    close(sockfd);
    return 0;}
void *handle_client(void *socket_desc) {
    int sock = *(int *)socket_desc;
    char buffer[BUFFER_SIZE];
    int n;
    char *start_ptr = buffer;
    int bytes_in_buffer = 0;
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        n = recv(sock, buffer, BUFFER_SIZE - 1, 0);
        if (n < 0) {
            perror("Error reading from socket");
            break;}
        if (n == 0) {
            printf("Client disconnected unexpectedly.\n");
            break;}
        bytes_in_buffer = n;
        start_ptr = buffer;
        while (bytes_in_buffer > 0) {
            char *newline_ptr = memchr(start_ptr, '\n', bytes_in_buffer);
            if (newline_ptr == NULL) {
                break;}
            int msg_length = newline_ptr - start_ptr;
            if (msg_length <= 0) {
                start_ptr = newline_ptr + 1;
                bytes_in_buffer -= (msg_length + 1);
                continue;}
            char message[BUFFER_SIZE];
            strncpy(message, start_ptr, msg_length);
            message[msg_length] = '\0';
            printf("Received message: %s\n", message);
            if (strncmp(message, "bye", 3) == 0) {
                printf("Client initiated termination.\n");
                close(sock);
                pthread_exit(NULL);}
            char ack_message[] = "ACK\n";
            n = send(sock, ack_message, strlen(ack_message), 0);
            if (n < 0) {
                perror("Error writing to socket");
                close(sock);
                pthread_exit(NULL);}
            start_ptr = newline_ptr + 1;
            bytes_in_buffer -= (msg_length + 1);}}
    close(sock);
    printf("Client handler thread terminated.\n");
    pthread_exit(NULL);}