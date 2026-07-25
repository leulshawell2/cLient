#include  <sys/socket.h>
#include <arpa/inet.h>

typedef char boolean;

typedef struct {
    void* buff;
    size_t size;
}tcp_packet;


typedef struct {
    int fd;
    boolean connected;
    int8_t attempt;
    struct sockaddr_in address;
    char* ip_str;
    uint16_t port;
}tcp_connection;
