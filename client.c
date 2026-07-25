#include <string.h>

#include  "helper.h"
#include  "client.h"
#include  "transport.c"

void http_request_set(http_request* req, int opt, void* value){
    switch (opt){
        case req_header:
            char* header = (char*)value;
            //calculate the length of the header
            size_t len = 0;
            while(header[len])
                len++;

            //check if first header
            if(req->headers == NULL)
                req->headers = malloc(0);


            size_t new_size = req->header_size + len + 1;
            char* h = (char*)realloc(req->headers, new_size + 1);  //+1 for NULL for printing and general safety

            strncpy(h, req->headers, req->header_size);
            h[req->header_size] = '\n';
            strncpy(h + req->header_size + 1, header, len);
            h[new_size] = '\0';


            req->headers = h;
            req->header_size = new_size;

            break;

        case req_host:
            req->host = (char*) value;
            break;

        case req_user:
            req->user_agent = (char*)value;
            
            char user_agent_header[MAX_CONTENT_LENGTH_BYTES + 20];
            snprintf(user_agent_header, MAX_CONTENT_LENGTH_BYTES + 20, "User-Agent:  %s", (char*)value);
            http_request_set(req, req_header, user_agent_header);
            break;

        case req_method:
            req->method = (char*)value;
            break;

        case req_body:
            char* body = (char*) value;

            if(req->method != METHOD_POST && req->method != METHOD_PUT){
                panic("Body not allowed for method %s", req->method);
            }

            req->body = body;
            
            //get the legth of the body and set the content length header
            size_t body_len = 0;
            while(body[body_len] != '\0')
                body_len++;

            char content_length_header[MAX_CONTENT_LENGTH_BYTES + 20];
            snprintf(content_length_header, MAX_CONTENT_LENGTH_BYTES + 20, "Content-Length:  %d", body_len);
            http_request_set(req, req_header, content_length_header);
            break;
        case req_resource:
            req->resource = (char*)value;
            break;
        default:
            break;
    }
}


void print_request(http_request* _req){
    printf("%s %s HTTP/%s", _req->method, _req->resource, HTTP_VERSION);
    printf("%s\n", _req->headers);   
    printf("%s\n", _req->body);
    
}


/**
 * This is blocking is won't return until the response comes or connection closes
 */

http_response http_send(tcp_connection* _conn, http_request* _req, request_config* _conf){
        //build the http reques string from the req object
        //send it over the tcp connection
        //wait and recieve all incomming response until timeout or http_response_end

        //parse the response string and build a reposne object

        //handle different status_codes based on config

        http_response res = {0};
        return res;
}
