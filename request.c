#include "request.h"
#include "config.h"

static void get_command_line(request_t * my_request);
static void parse_command_line(request_t * my_request);
static void get_file_path(request_t * my_request);

//init request
static request_t *
init_request(client_sockfd)
int client_sockfd;
{
    request_t * my_request;

    my_request                = (request_t *)malloc(sizeof(request_t));

    my_request->client_sockfd = client_sockfd;
    my_request->comm_line_size= 1024;
    my_request->comm_line     = (char *)malloc(my_request->comm_line_size);
    my_request->method_size   = 1024;
    my_request->url_size      = 1024;
    my_request->url           = (char *)malloc(my_request->url_size);
    my_request->file_path_size= 1024;
    my_request->file_path     = (char *)malloc(my_request->file_path_size);

    return my_request;
}

//do_request
request_t *
do_request(client_sockfd)
int client_sockfd;
{
    request_t * my_request;
    char * buf;

    //init request
    my_request = init_request(client_sockfd);

    //get command line
    get_command_line(my_request);

    //parse command line
    parse_command_line(my_request);

    //get file_path
    get_file_path(my_request);

    return my_request;
}

//get command line
static void
get_command_line(my_request)
request_t * my_request;
{
    int cur_index = 0;
    char cur_char = '\0';
    unsigned int comm_line_len;
    char buff[my_request->comm_line_size];
    unsigned int buff_len;

    comm_line_len = my_request->comm_line_size;
    recv(my_request->client_sockfd, buff, my_request->comm_line_size, 0);
    buff_len = strlen(buff);
    cur_char = buff[cur_index];
    while('\r' != cur_char && cur_index < buff_len-1)
    {
        *(my_request->comm_line+cur_index) = cur_char;
        cur_index ++;
        cur_char = buff[cur_index];
    }
    *(my_request->comm_line + cur_index)= '\0';
}

//parse_command_line
static void
parse_command_line(my_request)
request_t * my_request;
{
    int cur_index = 0;
    char cur_char = '\0';
    char * comm_line;
    char * method_buf;
    unsigned int method_off;
    char * url;

    
    method_buf = (char *)malloc(50);
    url        = (char *)malloc(1024);
    comm_line = my_request->comm_line;
    cur_char  = *(comm_line);
    while(!isspace(cur_char) && cur_index<50 -1)
    {
      *(method_buf + cur_index) = *(comm_line+cur_index);
      cur_index++;
      cur_char = *(comm_line+ cur_index);
    }
    *(method_buf+cur_index) = '\0';
    
    //get
    if(0 == strncasecmp(method_buf, "GET", 3))
    {
        my_request->method     = GET;
        my_request->method_off = cur_index+1;
	method_off             = cur_index+1;
    }

    //post
    if(0 == strncasecmp(method_buf, "POST",4))
    {
        my_request->method     = POST;
        my_request->method_off = cur_index+1;
        method_off             = cur_index+1;
    }

    //other
    //...

    //get url
    cur_index++;
    cur_char = *(comm_line+cur_index);
    while(!isspace(cur_char) && 
          cur_index-method_off<1024)
    {
      *(url+cur_index-method_off) = *(comm_line+cur_index);
      cur_index++;
      cur_char = *(comm_line+ cur_index);
    }
    *(url+ cur_index -method_off) = '\0';
    strcpy(my_request->url, url);
    free(url);
}

//get_file_path
static void
get_file_path(my_request)
request_t * my_request;
{
    char * template_file_path="./www/%s";
    char *buf;
    char cur_char='\0';
    int cur_index=0;
    int buf_index = 0;

    buf = (char *)malloc(1024);
    cur_char = *(my_request->url+cur_index);
    if('/' == cur_char)
	{
		cur_index++;
		cur_char = *(my_request->url+ cur_index);
    }
    while('?' != cur_char 
          && cur_index < strlen(my_request->url)  )
    {
        *(buf+buf_index) = cur_char;
        cur_index++;
		buf_index++;
        cur_char = *(my_request->url+cur_index);
    }
    *(buf+ buf_index)= '\0';

    sprintf(my_request->file_path, template_file_path, buf);
}
