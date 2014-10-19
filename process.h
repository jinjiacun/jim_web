#ifndef __PROCESS__
#define __PROCESS__
typedef struct process_s
{
	int pid;
	unsigned int flag;
}process_t;
extern void init_process(process_t * my_process, unsigned int len);
#endif
