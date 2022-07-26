#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>         // for data transfer
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

void endian_test(); // test endian print
int create_listening_socket(int port, string ip);   // create a listening socket

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
    int caddr_len;

    int ss = create_listening_socket(12905, "127.0.0.1");
    int cs = accept(ss, (sockaddr *)caddr, (socklen_t *)&caddr_len);

    string input;
    while(true)
    {
        cin >> input;
        if(input == "exit") break;

        write(cs, (void *)&input, input.length());
        cout << "message sent: " << input << endl;
    }

    close(cs);

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


int create_listening_socket(int port, string ip)
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
    int s = socket(PF_INET, SOCK_STREAM, 0);
    if (s == -1)
        return -1; // socket creation fail
    sockaddr_in *myaddr = new sockaddr_in();
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
    myaddr->sin_family = AF_INET;
    myaddr->sin_port = htons(port);
    myaddr->sin_addr.s_addr = inet_addr(ip.c_str());
    memset(myaddr->sin_zero, 0, sizeof(myaddr->sin_zero));

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
    if (bind(s, (struct sockaddr *)myaddr, sizeof(myaddr)) == -1)   // ignore red wiggly line
    {
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
    if (listen(s, 5) == -1)
    {
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

    return s;
}