#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
int main(){
    // khai bao socket
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    // khai bao dia chi server
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000);
   
    int res = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    
    if (res<0)
    {
        printf("Khong ket noi duoc voi server\n");
        return -1;
    }
    char buf[256];

    while(1) {
        //Nhan du lieu tu ban phims -> server
        printf("Nhap xau: ");
        fgets(buf, sizeof(buf), stdin);
        send(client, buf , strlen(buf), 0);
        //Nhan du liu tu server -> man hinh
        int ret = recv(client, buf, sizeof(buf) , 0);
        if (ret <= 0 ) 
            break;
        buf[ret] = 0;    
        printf("Received : %s\n", buf);
    }
    close(client);
    return 0;