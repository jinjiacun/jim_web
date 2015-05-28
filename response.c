#include "response.h"
#include "request.h"
#include "config.h"
#include "list.h"

extern enum ext_type;
static list_t * my_list;
static void set_status_code(response_t * my_response);
static void set_content_type(request_t * my_request, response_t * my_response);
static void set_head(response_t * my_response);
static void set_body(response_t * my_response,
                     request_t  * my_request);
static void do_send(response_t * my_response);
//查找点号最后出现的位置
static enum ext_type find_ext(char * file_name);

//init response
static response_t *
init_response(my_request)
request_t * my_request;
{
	response_t * my_response;

	my_response               = (response_t *)malloc(sizeof(response_t));
	my_response->client_sockfd= my_request->client_sockfd;
	my_response->content_type = (char *)malloc(1024);
	my_response->head         = (char *)malloc(1024);
	my_response->body         = (char *)malloc(4096);

	//init my_list

	my_list = list_init();

	return my_response;
}

void
do_response(my_request)
request_t * my_request;
{
	response_t * my_response;
	//init response
	my_response = init_response(my_request);

	//set satus code of response
	set_status_code(my_response);

	//set content_type
	set_content_type(my_request, my_response);

	//set head of response
	set_head(my_response);

	//set body of response
	set_body(my_response, my_request);

	//send
	do_send(my_response);
}

//set satus code of response
static void
set_status_code(my_response)
response_t * my_response;
{
    my_response->status_code = 200;
}

//set content_type
static void
set_content_type(my_request, my_response)
request_t * my_request;
response_t * my_response;
{
	struct stat info;

    if(stat(my_request->file_path, &info) <0)
	{
    	perror("info error\n");
    }
    else
    {
    	my_response->content_size = info.st_size;
    }
	//判定文件后缀名

   //my_response->content_type = "image/jpeg";
   //my_response->content_type = "text/html";
   //my_response->content_type = "image/webp";
}

//set head of response
static void
set_head(my_response)
response_t * my_response;
{
    sprintf(my_response->head,"HTTP/1.x %d OK \r\n \
                               Cache-Control: private\r\n \
                               Connection: Keep-Alive\r\n \
                               Content-Type: %s\r\n \
                               Transfer-Encoding: chunked\r\n \
                               Content-Length: %d\r\n\r\n",
	my_response->status_code, my_response->content_type, my_response->content_size);
}

//set body of response
static void
set_body(my_response, my_request)
response_t * my_response;
request_t * my_request;
{
    char *file_name;
    char * buff;
    int file_fd;
	struct stat info;
	int count;
	enum ext_type exec_type;

	file_name = my_request->file_path;

    printf("file:%s\n",file_name);
    if(stat(file_name, &info) <0)
		perror("info error\n");

    buff = (char *)malloc(CONTENT_LEN);
    memset(buff, 0, CONTENT_LEN);
	exec_type = find_ext(file_name);

	if(S_ISDIR(info.st_mode))
	{
		//dir
		strcpy(buff, "this is dir");
	}
	else if(PHP == exec_type)//判定是否是cgi
	{
		//执行php脚本
        //todo::
        if((file_fd = open("/dev/null", O_RDWR)) == 0)
        {
       		 perror("open file error");
        }

        close(file_fd);
	}
	else
	{
		//file
	    if((file_fd = open(file_name, O_RDONLY)) == 0)
   		 {
       		 perror("open file error");
   		 }
	    while((count = read(file_fd, buff, CONTENT_LEN))>0)
		{
		    printf("buff:%s,count:%d\n", buff, count);
			list_push(my_list, buff, count);
            memset(buff, 0, CONTENT_LEN);
		}
    	close(file_fd);
	}


    my_response->body  = my_list;
}

//查找点号最后出现的位置
static enum ext_type
find_ext(file_name)
char * file_name;
{
	char *cur_file_name;
    char *ext_name;
	char *html = "html";
	char *php = "php";
	const char split[] = ".";
    char *p= NULL;
	char *out=NULL;

	cur_file_name = malloc(sizeof(char *)*strlen(file_name));
	memcpy(cur_file_name, file_name, strlen(file_name));
	p = strtok_r(cur_file_name, split, &out);
	printf("p:%s\n", p);
	ext_name = p;
	while(NULL != p)
	{
		printf("p:%s\n", p);
	    ext_name = p;
    	p = strtok_r(NULL, split, &out);
	}
	/*
    p = strtok_r(NULL, split, &out);
	printf("p:%s\n", p);
	ext_name = p;
	*/
	/*
    while((p = strtok_r(cur_file_name, split, &out)) != NULL);
	{
		printf("p:%s\n", p);
		ext_name =  p;
	}
	*/

	//return PHP;

	if(!strcmp(ext_name, html))
	{
		return HTML;
	}
	else if(!strcmp(ext_name, php))
	{
		return PHP;
	}

	return UNKNOWN;
}

//send
static void
do_send(my_response)
response_t * my_response;
{
	int len;
	list_t * tmp_list;

	//send head
	send(my_response->client_sockfd, my_response->head,
         strlen(my_response->head), 0);
	while(NULL != (tmp_list= list_pop(my_list)))
	{
        send(my_response->client_sockfd,
        	 tmp_list->content,
         	 tmp_list->last,0);
		free(tmp_list);
	}
}
