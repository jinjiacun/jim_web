#ifndef __LIST__
#define __LIST__
#define NULL 0
#define CONTENT_LEN 10000
typedef struct list_s
{
	char content[CONTENT_LEN];
	unsigned int last;
	struct list_s * pre;
	struct list_s * next;
}list_t;

extern list_t * list_init();
extern void list_push(list_t * my_list, char * buf, unsigned int buf_size);
extern list_t * list_pop(list_t * my_list);
#endif
