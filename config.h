#ifndef __CONFIG__
#define __CONFIG__
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <memory.h>
#include <sys/select.h>
#define WWW_DIR "www"
#define MAX_PROCESS 8
#define FD_SETSIZE 1024
#define FIFO "/tmp/fifo"//有名管道信息
#define PHP_PATH "/usr/local/bin/php-cgi"

/*type of request*/
enum _req_type
{
	STATIC,
	DYNAMIC
};
#endif
