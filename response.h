#include "request.h"
#include "content_type.h"
#include "list.h"
#include<string.h>
#ifndef __RESPONSE__
#define __RESPONSE__
enum ext_type
{
	UNKNOWN,
    HTML,
	PHP
};
typedef struct
{
	int * client_sockfd;
	
	unsigned int status_code;
	content_type_t * content_type;
    long long content_size;
    char * head;
	list_t * body;
    //...
}response_t;
extern void do_response(request_t * my_request);
#endif
