#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

// Link references: https://medium.com/@shivambhadani_/understanding-tcp-and-building-our-own-tcp-server-in-c-language-8de9d9de78ef

int main()
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0)
    {
        perror("Socket creation failed");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("Binding failed");
        close(socket_fd);
        return 1;
    }

    if (listen(socket_fd, 3) < 0)
    {
        perror("Listening failed");
        close(socket_fd);
        return 1;
    }

    printf("Server is running and listening on port 8080...\n");

    while (1)
    {
        socklen_t addrlen = sizeof(addr);
        int client_id = accept(socket_fd, (struct sockaddr *)&addr, &addrlen);

        if (client_id < 0)
        {
            perror("Failed to accept connection");
            continue;
        }

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &addr.sin_addr, client_ip, sizeof(client_ip));
        printf("Client connected: %s\n", client_ip);

        char buffer[1024] = {0};
        ssize_t len = read(client_id, buffer, sizeof(buffer) - 1);

        if (len < 0)
        {
            perror("Error reading from client");
        }
        else if (len == 0)
        {
            printf("Client closed the connection.\n");
        }
        else
        {
            buffer[len] = '\0'; // Null-terminate the string
            printf("Received message: %s\n", buffer);
        }

        char *response = "Hello from the server!";
        int sent = write(client_id, response, strlen(response));

        if (sent < 0)
        {
            perror("Failed to send response");
        }

        // sleep(1);

        close(client_id);
        printf("Client disconnected.\n");
    }

    return 0;
}