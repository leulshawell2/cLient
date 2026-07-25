** cLEINT **


# If you don't want DNS and all the un-neccessary perks of other http clients

# Make sure you know you use case and http servers to use this. Some things may fail

#Exampe

```c
#include "client.c"

int main(){

    http_request req = {0};

    http_request_set(&req, req_host, "google.com");
    http_request_set(&req, req_resource_locator, "/search?query=what+the+f+is+going+on");
    http_request_set(&req, req_method, METHOD_POST);

    //set the request headers
    http_request_set(&req, req_header, "Content-Type: text/plain");
    http_request_set(&req, req_header, "Accept: text/plain");

    //set the user agent
    http_request_set(&req, req_user, "libcurl/1.0");

    http_request_set(&req, req_body, "username=username password=password");


    printf("%s\n", "connecting...");
    tcp_connection conn = tcp_connect("127.0.0.1", 4444);
    
    if(!conn.connected){
        panic("TCP connection failed  : (");
    }
    
    printf("%s\n", "connected  : )");

    request_config conf = {0};
    http_response http_res = http_send(&conn, &req, &conf);


    return 0;
}

```