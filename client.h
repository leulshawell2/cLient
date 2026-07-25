#include <stdio.h>


#define panic(format, ...) \
        fprintf(stderr, "PANIC at %s:%d in %s(): " format "\n", \
                __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
        exit(EXIT_FAILURE); \




#define MAX_CONTENT_LENGTH_BYTES 2
#define MAX_USER_AGENT_LENGTH  50
#define HTTP_VERSION  "1.1"


#define METHOD_POST "POST"
#define METHOD_GET "GET"
#define METHOD_PUT "PUT"
#define METHOD_QUERY "QUERY"
#define METHOD_DELETE "DELETE"

typedef enum {
    req_header,
    req_host   ,
    req_method,
    req_user  ,
    req_body  ,
    req_resource
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
    char* host;
    char* resource;
    char* headers; //Content-type: application/json
    size_t header_size;
    char* user_agent;
    char* method;
    char* body;

}http_request;
