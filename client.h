#define MAX_CONTENT_LENGTH_BYTES 2
#define MAX_USER_AGENT_LENGTH  50
#define HTTP_VERSION  "HTTP/1.1"


#define METHOD_POST "POST"
#define METHOD_GET "GET"
#define METHOD_PUT "PUT"
#define METHOD_QUERY "QUERY"
#define METHOD_DELETE "DELETE"

/*
this magic number is to be added to request size when allcating meme
it is to conpensate for the mem requred for method and some http specific data that
have know max size
10 for 6->method max size and 4 for the "\r\n\r\n"
*/
#define HTTP_MAX_PADDING   10

typedef enum {
    req_header,
    req_host   ,
    req_method,
    req_user  ,
    req_body  ,
    req_resource_locator
}req_opts;


typedef struct {
    unsigned int time_out_mili; 
    char    follow_redirect;
}request_config;

// Structure to safely hold response data in memory
struct MemoryBuffer {
    char *response;
    size_t size;
};

typedef struct {
    int satus;
    char* content;
    size_t content_len;


} http_response;


typedef struct {
    char* headers;
    size_t size;
}headers;


typedef struct {
    char* host;
    char* resource;
    char* method;
    
    char* headers;
    char* user_agent;
    
    char* body;

    size_t header_size;
    size_t body_size;
    size_t rl_size;

}http_request;
