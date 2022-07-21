#include <iostream>
#include <sys/socket.h>

using namespace std;

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
    int s = socket(AF_INET, SOCK_STREAM, 0);
    

    return 0;
}
