#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#define CHAT_PORT 6000
#define MSG_SIZE 1024
int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_info, client_info;
    char msg_buffer[MSG_SIZE];
    fd_set socket_set;
    int highest_socket, event_count, msg_length, client_addr_size;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);}
    server_info.sin_family = AF_INET;
    server_info.sin_addr.s_addr = INADDR_ANY;
    server_info.sin_port = htons(CHAT_PORT);
    if (bind(server_socket, (struct sockaddr*)&server_info, sizeof(server_info)) < 0) {
        perror("Failed to bind socket");
        close(server_socket);
        exit(EXIT_FAILURE);}
    if (listen(server_socket, 3) < 0) {
        perror("Listen error");
        close(server_socket);
        exit(EXIT_FAILURE);}
    printf("Server is running.\n");
    client_addr_size = sizeof(client_info);
    client_socket = accept(server_socket, (struct sockaddr*)&client_info, (socklen_t*)&client_addr_size);
    if (client_socket < 0) {
        perror("Client connection failed");
        close(server_socket);
        exit(EXIT_FAILURE);}
    printf("Client connected.\n");
    while (1) {
        FD_ZERO(&socket_set);
        FD_SET(0, &socket_set);       
        FD_SET(client_socket, &socket_set); 
        highest_socket = client_socket;
        event_count = select(highest_socket + 1, &socket_set, NULL, NULL, NULL);
        if (event_count < 0) {
            perror("Select failed");
            break;}
        if (FD_ISSET(0, &socket_set)) {
            fgets(msg_buffer, MSG_SIZE, stdin);
            send(client_socket, msg_buffer, strlen(msg_buffer), 0);
            printf("Server: %s", msg_buffer);
            if (strncmp(msg_buffer, "bye", 3) == 0) {
                printf("Server has disconnected.\n");
                break;}}
        if (FD_ISSET(client_socket, &socket_set)) {
            memset(msg_buffer, 0, MSG_SIZE);
            msg_length = read(client_socket, msg_buffer, MSG_SIZE);
            if (msg_length == 0 || strncmp(msg_buffer, "bye", 3) == 0) {
                printf("Client disconnected.\n");
                break;}
            printf("Client: %s", msg_buffer);}}
    close(client_socket);
    close(server_socket);
    return 0;}