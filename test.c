#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct list_t list_t;
struct list_t
{
	char content[1024];
	list_t * next;
};

list_t * list_init();
int list_add(list_t * my_list, char * buf, int buf_size);
#define list_foreach(item ,  my_list) \
        for(item=my_list->nex;item<>NULL; item=item->next) ; 
		

int
main()
{
  list_t * my_list, tmp_list;
  char * tmp_char;

  my_list = list_init();
  if(NULL == my_list)
	return 0;

  tmp_char = (char *)malloc(1024);
  strcpy(tmp_char, "first test");
  list_add(my_list, tmp_char, strlen(tmp_char));

  memset(tmp_char, 0, 1024);
  strcpy(tmp_char, "second test");
  list_add(my_list, tmp_char, strlen(tmp_char));
  list_foreach(tmp_list , my_list)
  {
    printf("item:%s\n", tmp_list);
  }
  
  return 0;
}

list_t *
list_init()
{
	list_t * my_list;
	my_list = (list_t *)malloc(sizeof(list_t));
	if(NULL == my_list)
		return NULL;

	strcpy(my_list->content, "");
	my_list->next = NULL;

	return my_list;
}

int list_addr(my_list, buf, buf_size)
list_t * my_list;
char * buf;
int buf_size;
{
	list_t * tmp_list;
	
	tmp_list = (list_t *)malloc(sizeof(list_t));
    if(NULL == tmp_list)
		return NULL;

    if(buf_size > 1023)
		return NULL;

    strcpy(tmp_list->content, buf);
	tmp_list->next = my_list->next;
    my_list->next = tmp_list;    
	
	return true;
}
