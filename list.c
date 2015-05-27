#include "list.h"

list_t *
list_init()
{
	list_t * tmp_list;

	tmp_list = (list_t *)malloc(sizeof(list_t));
	if(0 == tmp_list) return 0;
	
	tmp_list->next = tmp_list;
	tmp_list->pre  = tmp_list;
	
	return tmp_list;  
}

void
list_push(my_list, buf, buf_size)
list_t * my_list;
char * buf;
unsigned int buf_size;
{
	list_t * tmp_list;

	tmp_list = (list_t *)malloc(sizeof(list_t));
	if(0 == tmp_list) return;

	if(buf_size <= CONTENT_LEN)
	{
	//	strcpy(tmp_list->content, buf);
        memcpy(tmp_list->content, buf, buf_size);
		tmp_list->last     = buf_size;

		tmp_list->next     = my_list->next;
		my_list->next->pre = tmp_list;
		my_list->next      = tmp_list;
		tmp_list->pre      = my_list;
	}
}

list_t *
list_pop(my_list)
list_t * my_list;
{
	list_t * tmp_list;
    
    if(my_list != my_list->pre
      && my_list != my_list->next)
	{
		tmp_list = my_list->pre;

		tmp_list->pre->next = my_list;
        my_list->pre        = tmp_list->pre;
	}
    else
	{
        return 0;
    }

	return tmp_list;
}

