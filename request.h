#ifndef __REQUEST__
#define __REQUEST__
enum request_method {GET,POST};
enum request_source {IS_DIR,IS_FILE};
enum request_file_type {NO_FILE,TEXT, JPEG};
typedef struct
{
	int * client_sockfd;

	char * comm_line;
	unsigned int comm_line_size;
	enum request_method method;
	unsigned int method_size;
	unsigned int method_off;

	char * url;
	unsigned int url_size;

/*	_req_type req_type;*/


    enum request_source source_type;
	char * file_path;
    enum request_file_type file_type;
	unsigned int file_path_size;
	//...
}request_t;

extern request_t * do_request(int client_sockfd);
#endif
