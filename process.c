#include "process.h"

void init_process(my_process, len)
process_t * my_process;
unsigned int len;
{
	process_t * tmp_p;
	unsigned int max_len;
	int pid;
	
    max_len = len; 
    for(tmp_p = my_process; 
        tmp_p < my_process+max_len ; 
        tmp_p++)
	{
        pid = fork();
		if(0 == pid)//parent's process
		{
		
		}
		else if(0 < pid)//child's process
		{
			tmp_p->pid  = pid;
			tmp_p->flag = 0;
		}
	}
      
}
