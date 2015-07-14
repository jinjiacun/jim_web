#ifndef __REQUEST__
#define __REQUEST__
typedef enum {GET,POST} METHOD;
enum request_source {IS_DIR,IS_FILE};
enum request_file_type {NO_FILE,TEXT, JPEG};

/*param of request*/
typedef struct param * in_param;
typedef struct param
{
	char name[100];
	char value[100];	
};

typedef struct
{
	int * client_sockfd;

	char * comm_line;
	unsigned int comm_line_size;
	METHOD method;
	char * method_last;
	unsigned int method_size;

	char * url_last;
	unsigned int url_size;

	/*	_req_type req_type;*/


    enum request_source source_type;
	char * file_path;
    enum request_file_type file_type;
	unsigned int file_path_size;

	/*param of request
	in_param param_l;
	unsigned int param_l_len
	*/;
	//...
}request_t;

extern request_t * do_request(int client_sockfd);
#endif
