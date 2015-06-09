#include "config.h"
#include "cgi.h"

//访问php
void
call_php(file_name, list)
char * file_name;
char ** list;
{
	int fd;
	int pid;
	char buff[4096];
	int res;
	int size;

	if(access(FIFO, F_OK) == -1)
	{
		res = mkfifo(FIFO, 0777);
		if(0 != res)
		{
			printf("no create fifo\n");
			exit(1);
		}
	}
	
	fd = open(FIFO, O_RDWR|O_NONBLOCK);
    if(fd <0)
	{
		printf("open fifo err\n");
		exit(0);
	}

	pid = fork();
	switch(pid)
	{    
		case 0://child of process
			{
				close(1);
				dup2(fd, 1);
				close(fd);
				char *args[2];
				args[0] = "-f";
				//args[1] = file_name;
				args[1] = "/opt/jim_web/www/index.php";
				execv(PHP_PATH, args);	
				printf("child err\n");
			}
		default:
			{	
				waitpid(pid);
				read(fd, buff, 53);
				memset(buff, 0, 53);
				while(size = read(fd, buff, 4096))
				{
					list_push(list, buff, size);
					memset(buff, 0, size);
					if(size <4096)
						break;
				}
			} 
	}

	
}
