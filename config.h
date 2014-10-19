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
#endif
