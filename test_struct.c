#include<stdio.h>
#include<stdlib.h>
#define MAX 3

struct node
{
	int i;
	int j;
};

struct node my_node[MAX];

int
main()
{
	struct node * p_node;
	//init
    int index;
    int len;

    index = 0;
	for(p_node = my_node; 
	    p_node < my_node+MAX; 
        p_node++)
	{	
		index++;
		p_node->i = index;
		p_node->j = index+1;
	}

	//show
	//for(p_node = my_node; p_node; p_node++)
	//{
	//	printf("node i:%d, j:%d \n", p_node->i, p_node->j);
	//}

	return 0;
}
