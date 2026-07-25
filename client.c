#include <stdlib.h>
#include <string.h>

#include  "client.h"





void http_request_set(http_request* _req, int opt, void* value){
    switch (opt){
        case req_header:
            char* header = (char*)value;
            //calculate the length of the header
            size_t len = 0;
            while(header[len])
                len++;

            //check if first header
            if(_req->headers == NULL)
                _req->headers = malloc(0);


            size_t new_size = _req->header_size + len + 1;
            char* h = (char*)realloc(_req->headers, new_size + 1);  //+1 for NULL for printing and general safety

            strncpy(h, _req->headers, _req->header_size);
            h[_req->header_size] = '\n';
            strncpy(h + _req->header_size + 1, header, len);
            h[new_size] = '\0';


            _req->headers = h;
            _req->header_size = new_size;

            break;

        case req_host:
            _req->host = (char*) value;
            break;

        case req_user:
            _req->user_agent = (char*)value;
            
            char user_agent_header[MAX_CONTENT_LENGTH_BYTES + 20];
            snprintf(user_agent_header, MAX_CONTENT_LENGTH_BYTES + 20, "User-Agent:  %s", (char*)value);
            http_request_set(_req, req_header, user_agent_header);
            break;

        case req_method:
            _req->method = (char*)value;
            break;

        case req_body:
            char* body = (char*) value;

            if(_req->method != METHOD_POST && _req->method != METHOD_PUT){
                panic("Body not allowed for method %s", _req->method);
            }
            
            _req->body = body;

            
            //get the legth of the body and set the content length header
            size_t body_len = 0;
            while(body[body_len] != '\0')
                body_len++;

            char content_length_header[MAX_CONTENT_LENGTH_BYTES + 20];
            snprintf(content_length_header, MAX_CONTENT_LENGTH_BYTES + 20, "Content-Length:  %d", body_len);
            http_request_set(_req, req_header, content_length_header);
            break;
        case req_resource:
            _req->resource = (char*)value;
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

void http_send_request(http_request* _req){
    //this is the transport layer
    //try to keep it as simple as f possible
}
