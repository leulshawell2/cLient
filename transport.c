#include "transport.h"
#include "helper.h"
#include <sys/socket.h>
#include <netinet/in.h>




ssize_t _sendn(int fd, const void *buf, size_t n) {
    size_t sent = 0;
    const uint8_t *ptr = (const uint8_t *)buf;

    while (sent < n) {
        ssize_t s = send(fd, ptr + sent, n - sent, 0);
        if (s < 0) continue;

        sent += (size_t)s;
    }
    return (ssize_t)sent;
}

tcp_connection tcp_connect(char* ip, uint16_t port){
    tcp_connection conn = {.ip_str=ip, .port=port};

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr_in = { .sin_port=htons(port), .sin_family=AF_INET};


    if(inet_pton(AF_INET, ip, &addr_in.sin_addr) < 0){
        panic("Error setting    up address")
    }

    
    if(connect(socket_fd, (struct sockaddr *)&addr_in, sizeof(addr_in)) < 0){
        conn.attempt += 1;
        return conn;
    }
    
    conn.connected = 1;
    conn.address = addr_in;
    conn.fd = socket_fd;

    return conn;
}




int tcp_send_packet(tcp_connection* _conn, tcp_packet* pac){
    uint32_t net_len = htonl(pac->size);

    if (_conn->connected){
        if (_sendn(_conn->fd, &net_len, sizeof(net_len)) < 0) return -1;
        if (_sendn(_conn->fd, pac->buff, pac->size) < 0) return -1;
    }else {
        panic("TCP is not connected. Connect first");
    }
}


