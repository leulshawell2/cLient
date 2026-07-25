#include "client.c"

int main(){

    http_request req = {0};

    http_request_set(&req, req_host, "google.com");
    http_request_set(&req, req_resource, "/search?query=what+the+f+is+going+on");
    http_request_set(&req, req_method, METHOD_PUT);

    //set the request headers
    http_request_set(&req, req_header, "Content-Type: text/plain");
    http_request_set(&req, req_header, "Accept: text/plain");

    //set the user agent
    http_request_set(&req, req_user, "libcurl/1.0");

    http_request_set(&req, req_body, "username=username password=password");

    printf("%s\n", "connecting...");

    tcp_connection conn = tcp_connect("192.168.1.1", 443);
    
    if(!conn.connected){
        panic("TCP connection failed  : (");
    }
    
    printf("%s\n", "connected  : )");

    request_config conf = {0};
    http_response http_res = http_send(&conn, &req, &conf);
    

    return 0;
}