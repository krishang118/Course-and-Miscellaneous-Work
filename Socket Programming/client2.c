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
    int chat_socket;
    struct sockaddr_in server_info;
    char msg_buffer[MSG_SIZE];
    fd_set socket_set;
    int highest_socket, event_count, msg_length;
    chat_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (chat_socket < 0) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);}
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(CHAT_PORT);
    server_info.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(chat_socket, (struct sockaddr*)&server_info, sizeof(server_info)) < 0) {
        perror("Connection to server failed");
        close(chat_socket);
        exit(EXIT_FAILURE);}
    printf("Connected to server.\n");
    while (1) {
        FD_ZERO(&socket_set);
        FD_SET(0, &socket_set);      
        FD_SET(chat_socket, &socket_set);  
        highest_socket = chat_socket;
        event_count = select(highest_socket + 1, &socket_set, NULL, NULL, NULL);
        if (event_count < 0) {
            perror("Select failed");
            break;}
        if (FD_ISSET(0, &socket_set)) {
            fgets(msg_buffer, MSG_SIZE, stdin);
            send(chat_socket, msg_buffer, strlen(msg_buffer), 0);
            printf("Client: %s", msg_buffer);
            if (strncmp(msg_buffer, "bye", 3) == 0) {
                printf("Client has disconnected.\n");
                break;}}
        if (FD_ISSET(chat_socket, &socket_set)) {
            memset(msg_buffer, 0, MSG_SIZE);
            msg_length = read(chat_socket, msg_buffer, MSG_SIZE);
            if (msg_length == 0 || strncmp(msg_buffer, "bye", 3) == 0) {
                printf("Server disconnected.\n");
                break;}
            printf("Server: %s", msg_buffer);}}
    close(chat_socket);
    return 0;}