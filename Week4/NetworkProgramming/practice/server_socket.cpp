#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>         // for data transfer
#include <arpa/inet.h>
#include <sys/socket.h>

#include <fcntl.h>

using namespace std;

void endian_test(); // test endian print
int create_listening_socket(sockaddr_in *myaddr, int port, string ip);   // create a listening socket

int main(int argc, char const *argv[])
{
    /*
     * int sockfd = socket(domain, type, protocol)
     * socket returns 'socket descriptor'(sockfd) on success
     *
     * domain
     *   - same host                                    AF_ LOCAL
     *   - process on different host across IPV4        AF_INET
     *   - IPV6                                         AF_INET6
     *
     * type
     *   - TCP                                          SOCK_STREAM
     *   - UDP                                          SOCK_DGRAM
     *
     * protocol
     *   - IP(Internet Protocol)                        0
     */

    sockaddr_in *myaddr = new sockaddr_in();
    sockaddr_in *caddr = new sockaddr_in();
    unsigned int caddr_len;

    int ss_fd = create_listening_socket(myaddr, 80, "127.0.0.1");
    if(ss_fd == -1)
    {
        cout << "failed to create listening socket" << endl;
        return 1;
    }
    int cs_fd = accept(ss_fd, (sockaddr *)caddr, &caddr_len);

    cout << "client fd: " << cs_fd << endl << endl;

    char message[1000];
    int msg_len;

    msg_len = read(cs_fd, message, sizeof(message)-1);
    cout << message << endl;

    // string header = "test";
    // "HTTP/1.1 200 OK\n";
    // "Date: Fri, 01 Feb 2002 01:34:56 GMT\n";
    // "Server: Apache/1.3.19 (Unix) PHP/4.0.6\n";
    // "X-Powered-By: PHP/4.0.6\n";
    // "Connection: close\n";
    // "Content-Length: 3\n";
    // "Content-Type: text/html\n\n";

    // send(cs_fd, header.c_str(), header.length(), 0);

    // write(cs_fd, header.c_str(), header.length());



    // cout << "header: " << header << endl << endl;

    int fd = open("index.html", O_RDONLY);
    cout << "fd: " << fd << endl;
    char buf_out[1024];
    int n;
    while ( (n = read(fd, buf_out, 255)) > 0)    
    {
        write(cs_fd, buf_out, n);
        bzero(buf_out, 255);
    }

    char *m2;
    int si;

    msg_len = read(cs_fd, message, sizeof(message)-1);
    cout << message << endl;

    // int i = 0;
    // string s;
    // while(true)
    // {
    //     sleep(1);
    //     s = to_string(i++);
    //     s += "\n";
    //     write(cs_fd, s.c_str(), s.length());
    //     if(i==5) break;
    // }
    
    write(cs_fd, "hi yolo\n", 8);

    // string input;
    // while(true)
    // {
    //     cin >> input;
    //     if(input == "exit") break;
    //     input += "\r\n";
    //     write(cs_fd, input.c_str(), input.length());
    //     cout << "message sent: " << input << endl;
    // }

    if (shutdown(cs_fd, SHUT_RDWR) == 0)
        cout << "shutdown complete" << endl;
    shutdown(ss_fd, SHUT_RDWR);
    close(cs_fd);
    close(ss_fd);
    close(fd);
    cout << "all sockets closed!" << endl;

    return 0;
}

void endian_test()
{
    in_addr_t a = inet_addr("1.2.3.4");
    char *c = (char *)&a;
    for (int i = 0; i < 4; i++)
    {
        cout << (int)*(c + i) << endl;
    }
}


int create_listening_socket(sockaddr_in *myaddr, int port, string ip)
{
    /*
     * int socket(int domain, int type, int protocol);
     *
     * :: domain ::
     *  communication domain
     *      - AF_INET   /   PF_INET
     *      - AF_INET6  /   PF_INET6
     *
     * :: type ::
     *  communication type
     *      - SOCK_STREAM
     *      - SOCK_DGRAM
     *
     * :: protocol ::
     *  Protocol value for Internet Protocol(IP)
     *  This is the same number which appears on protocol field in the IP header of a packet.
     */
    int ss = socket(PF_INET, SOCK_STREAM, 0);
    if (ss == -1)
    {
        cout << "failed to create socket" << endl;
        return -1; // socket creation fail
    }

    // sockaddr_in *myaddr = new sockaddr_in();
    /*
     * sockaddr_in
     *
     * :: sin_family ::
     *  AF_INET
     *  AF_INET6
     *  AF_LOCAL
     *      what does AF mean?
     *
     * :: sin_port ::
     *  16bit Network byte
     * 
     * :: sin_addr.s_addr ::
     * 
     * :: sin_zero ::
     */

    memset(myaddr->sin_zero, 0, sizeof(myaddr->sin_zero));
    myaddr->sin_family = AF_INET;
    myaddr->sin_port = htons(port);
    myaddr->sin_len = sizeof(*myaddr);      // not sure
    // myaddr->sin_addr.s_addr = inet_addr(ip.c_str());
    myaddr->sin_addr.s_addr = htonl(INADDR_ANY);
    // inet_addr();
    // inet_aton();


    /*
     * int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
     *
     * :: sockfd ::
     *  socket file descripter
     * 
     * :: myaddr ::
     *  struct used for storing IP address
     * 
     * :: addrlen
     *  what is this?
     */
    if (bind(ss, (sockaddr *)myaddr, sizeof(*myaddr)) == -1)   // ignore red wiggly line
    {
        cout << "failed to bind socket" << endl;
        return -1; // socket bind fail
    }

    /*
     * int listen(int sockfd, int backlog);
     * 
     * :: sockfd ::
     * 
     * :: backlog ::
     *  specifies the number of pending connections the queue will hold.
     *
     */
    if (listen(ss, 5) == -1)
    {
        cout << "failed to listen socket" << endl;
        return -1; // socket listen fail
    }

    /*
     * int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
     *  - returns fd (file descriptor) of the connected socket
     * 
     * :: sockfd ::
     * 
     * :: addr ::
     *  pass variable to save socket address of connected device
     * 
     * :: addrlen ::
     *  pass variable to save socket address length
     *
     */

    return ss;
}