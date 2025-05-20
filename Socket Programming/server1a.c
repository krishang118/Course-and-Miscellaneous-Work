#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define SERVER_PORT 6000
#define MSG_SIZE 1024
int main() {
    int server_sock, client_sock;
    socklen_t addr_len;
    struct sockaddr_in server_addr, client_addr;
    char msg_buffer[MSG_SIZE];
    int bytes_received;
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);}
    memset((char *)&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;              
    server_addr.sin_addr.s_addr = INADDR_ANY;      
    server_addr.sin_port = htons(SERVER_PORT);    
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_sock);
        exit(EXIT_FAILURE);}
    listen(server_sock, 5);
    printf("Server is running.\n");
    addr_len = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_len);
    if (client_sock < 0) {
        perror("Accept failed");
        close(server_sock);
        exit(EXIT_FAILURE);}
    printf("Client connected.\n");
    while (1) {
        memset(msg_buffer, 0, MSG_SIZE);
        bytes_received = recv(client_sock, msg_buffer, MSG_SIZE - 1, 0);
        if (bytes_received < 0) {
            perror("Failed to read from socket");
            break;}
        printf("Message from client: %s\n", msg_buffer);
        if (strncmp(msg_buffer, "bye", 3) == 0) {
            printf("Client requested termination.\n");
            break;}
        bytes_received = send(client_sock, "ACK", strlen("ACK"), 0);
        if (bytes_received < 0) {
            perror("Failed to write to socket");
            break;}}
    close(client_sock);
    close(server_sock);
    printf("Server has been closed.\n");
    return 0;}