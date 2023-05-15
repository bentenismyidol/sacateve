#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <poll.h>

int main() {
    // Khai báo socket client
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Khai báo địa chỉ server
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000); 

    // Thực hiện kết nối đến server
    int res = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if (res == -1) {
        printf("Khong ket noi duoc den server!\n");
        return 1;
    }
    struct pollfd fds[2];
    fds[0].fd = STDERR_FILENO;
    fds[0].events = POLLIN;
    fds[1].fd = client;
    fds[1].events = POLLIN;

    char buffer[256];
    while (1)
    {
        int ret = poll(fds, 2 , -1);
        if (ret < 0) {
            perror("poll() failed");
            break;
        }
        if (fds[0].revents & POLLIN) {
            //sk co du lie tu ban phim
            fgets(buffer, sizeof(buffer), stdin);
            send(client, buffer, strlen(buffer), 0);

        }
        if (fds[1].events & POLLIN) {
            ret = recv(client, buffer, sizeof(buffer), 0);
            if (ret <=0) {
                break;
                buffer[ret] = 0;
                printf("Received: %s\n", buffer);
            }
        }
    }
    
}