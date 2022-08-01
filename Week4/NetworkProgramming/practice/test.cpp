#include <sys/types.h>

#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>

#include <arpa/inet.h>
#include <fcntl.h>

#define SA    struct sockaddr

int main(int argc, char **argv)
{
    int i, maxi, sockfd;
    int nread;
    int state = 0;
    int port;
    int n;
    int fd;
    int clilen;

    char buf_out[1024];
    char buf_in[1024];
    char *header;

    int server_sockfd, client_sockfd;

    struct sockaddr_in clientaddr, serveraddr;

    // socket 함수를 이용해서 end-point 소켓을 
    // 만든다.
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);    
    bzero(&serveraddr, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(8080);

    // 소켓특성을 묶어준다. 
    bind (server_sockfd, (SA *)&serveraddr, sizeof(serveraddr));
    if ((state = listen(server_sockfd, 5)) == -1)
    {
        perror("listen error : ");
        exit;
    }

    header = "HTTP/1.1 200 OK\n"
    "Date: Fri, 01 Feb 2002 01:34:56 GMT\n"
    "Server: Apache/1.3.19 (Unix) PHP/4.0.6\n"
    "X-Powered-By: PHP/4.0.6\n"
    "Connection: close\n"
    "Content-Type: text/html\n\n";

    while(1)
    {
        clilen = sizeof(clientaddr);

        // socket() 함수를 이용해서 만들어진 end-point 소켓지정번호인 
        // server_sockfd 에 연결이 들어오는지를 기다린다.  
        if ((client_sockfd = accept(server_sockfd, (SA *)&clientaddr, &clilen)) == -1)
        {
            perror("accept error : ");
            close(client_sockfd);
        }

        fd = open("/root/index.html", O_RDONLY);

        memset(buf_in, 0x00, 1024);
        while ((n = read(client_sockfd, buf_in, 1024)) > 0)
        {
            break;
        }

        printf("ok end\n");
        write(client_sockfd, header, strlen(header)); 

        while ( (n = read(fd, buf_out, 255)) > 0)    
        {
            write(client_sockfd, buf_out, n);
            bzero(buf_out, 0x00, 255);
        }
        close(client_sockfd);
    }
}