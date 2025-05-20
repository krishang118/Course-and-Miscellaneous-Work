#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SERVER_PORT 6000
#define MSG_SIZE 1024
int main() {
    int client_sock;
    struct sockaddr_in server_addr;
    char msg_buffer[MSG_SIZE];
    int bytes_sent;
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);}
    memset((char *)&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;              
    server_addr.sin_port = htons(SERVER_PORT);     
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        close(client_sock);
        exit(EXIT_FAILURE);}
    if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(client_sock);
        exit(EXIT_FAILURE);}
    printf("Connected to server.\n");
    while (1) {
        memset(msg_buffer, 0, MSG_SIZE);
        strcpy(msg_buffer, "hello");
        bytes_sent = send(client_sock, msg_buffer, strlen(msg_buffer), 0);
        if (bytes_sent < 0) {
            perror("Failed to write to socket");
            break;}
        printf("Sent: %s\n", msg_buffer);
        memset(msg_buffer, 0, MSG_SIZE);
        bytes_sent = recv(client_sock, msg_buffer, MSG_SIZE - 1, 0);
        if (bytes_sent < 0) {
            perror("Failed to read from socket");
            break;}
        printf("Received: %s\n", msg_buffer);
        printf("Send another message? (y/n): ");
        char user_choice;
        scanf(" %c", &user_choice);
        while (getchar() != '\n');
        if (user_choice == 'n' || user_choice == 'N') {
            strcpy(msg_buffer, "bye");
            bytes_sent = send(client_sock, msg_buffer, strlen(msg_buffer), 0);
            if (bytes_sent < 0) {
                perror("Failed to write to socket");}
            printf("Sent 'bye' to server.\n");
            break;}}
    close(client_sock);
    printf("Client closed.\n");
    return 0;}