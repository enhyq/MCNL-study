#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

int create_socket();

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

    in_addr_t a = inet_addr("1.2.3.4");
    char *c = (char*)&a;
    for(int i=0; i<4; i++) {
        cout << (int)*(c+i) << endl;
    }

    return 0;
}

int create_socket()
{
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
        return s;
    sockaddr_in *myaddr = new sockaddr_in();
    /*
     * :: sin_family ::
     *  AF_INET
     *  AF_INET6
     *  AF_LOCAL
     *      what does AF mean?
     *
     * :: sin_port ::
     *  16bit Network byte
     */
    myaddr->sin_family = AF_INET;
    myaddr->sin_port = htons(23415);
    myaddr->sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(myaddr->sin_zero, 0, sizeof(myaddr->sin_zero));

    if(bind(s, (struct sockaddr *)myaddr, sizeof(myaddr)==-1) == -1)
    {

    }
        
    

    // bind(s, (sockaddr *)myaddr, sizeof(myaddr) == -1);

    listen(s, 5);

    return s;
}