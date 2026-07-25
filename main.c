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


    print_request(&req);
 


    return 0;
}