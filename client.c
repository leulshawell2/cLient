// #include <stdio.h>
#include <stdlib.h> //mem alloc
#include <string.h> //string paring and copy
#include <curl/curl.h>  //http calls



typedef enum {
    req_header,
    req_url   ,
    req_method,
    req_user  
}req_opts;



// Structure to safely hold response data in memory
struct MemoryBuffer {
    char *response;
    size_t size;
};

typedef struct {
    int satus;
    char* content;
    size_t length;

} http_reposne;


typedef struct {
    char* headers;
    size_t size;
}headers;


typedef struct {
    char* url;
    headers* headers; //Content-type: application/json
    char* user_agent;

}http_request;




void http_client_init(){
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl_easy_init();

}





void http_request_set(http_request* _req, int opt, void* value){
    switch (opt){
        case req_header:
            char* header = (char*)value;
            //calculate the length of the header
            size_t len = 0;            
            while(header[len])
                len++;
            len++;
            
            //check if first header
            if(_req->headers == NULL){
                headers header = {headers: malloc(0), size: 0};
                _req->headers = &header;
            }
            
            void* h = realloc(_req->headers->headers, _req->headers->size + len + 1);  //+1 for the new line am gonna add in the middle
            strncpy(h, _req->headers->headers, _req->headers->size); //copy the old to new mem
            strncpy(h + _req->headers->size + 1, _req->headers->headers, _req->headers->size); //copy the new header
            ((char*)h)[_req->headers->size] = '\n'; //add new line between
            printf("%s\n", (char*)h);
            
            _req->headers->headers = h;



            break;
        case req_url:
            _req->url = (char*) value;
            break;

        case req_user:
            _req->user_agent = (char*)value;
            break;

        default:
            break;
    }

}

void http_client_cleaup(){


}
    
void parse(http_reposne* _res , void* _buff){

}

void http_call(http_request req){

}


void handle_http(http_reposne* _res){
    //some http call
    void* _buff;
    parse(_res, _buff);
}


int main(){

    http_request req = {0};
    
    //set the reques url
    http_request_set(&req, req_url, "https://google.com?query=what+the+f+is+going+on");

    //set the request headders
    http_request_set(&req, req_header, "Content-type:text/plain");
    // http_request_set(&req, req_header, "Accept:text/plain");

    //set the user agent
    http_request_set(&req, req_user, "libcurl/1.0");

    printf("%s\n", req.headers->headers);



    return 0;   
}