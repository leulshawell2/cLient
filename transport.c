#include "transport.h"
#include "helper.h"
#include <sys/socket.h>
#include <netinet/in.h>



tcp_connection tcp_connect(char* ip, uint16_t port){
    tcp_connection conn = {.ip_str=ip, .port=port};

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr_in = { .sin_port=htons(port), .sin_addr={0}};

    inet_pton(AF_INET, ip, &addr_in.sin_addr);
    
    int success = connect(socket_fd, (struct sockaddr *)&addr_in, sizeof(struct sockaddr_in));
    
    if(success < 0){
        panic("Tcp Connect Failed");
    }
    
    conn.connected = 1;
    conn.address = addr_in;
    conn.fd = socket_fd;

    return conn;
}




void tcp_send_packet(tcp_packet* pac, tcp_connection conn){
    if (conn.connected){
        send(conn.fd, pac->buff, pac->size, 0);
    }else {

    }
}


