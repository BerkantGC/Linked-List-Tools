#include <stdio.h>
#include <stdlib.h>

typedef struct LINKED_LIST_NODE_s *LINKED_LIST_NODE;

typedef struct LINKED_LIST_NODE_s{
	LINKED_LIST_NODE next; /*Do not change the order.*/
	void *data;
} LINKED_LIST_NODE_t[1];

  typedef struct LINKED_LIST_s *LINKED_LIST;
  typedef struct LINKED_LIST_s{
  LINKED_LIST_NODE head; /*May overlap with next.*/
  } LINKED_LIST_t[1];

LINKED_LIST linked_list_init()
{
	LINKED_LIST list = NULL;
	
	list = (LINKED_LIST)malloc(sizeof(LINKED_LIST_t));
	if(list != NULL)
	{
		list->head = NULL;
	}
	
	return list;
}

void linked_list_free(LINKED_LIST list)
{
	LINKED_LIST_NODE iter;
	
	while(list->head != NULL)
	{
		iter = list->head;
		list->head = list->head->next;
		free(iter);
	}
}

void linked_list_prepend(LINKED_LIST list, void *data)
{
	LINKED_LIST_NODE node = (LINKED_LIST_NODE)malloc(sizeof(LINKED_LIST_NODE_t));
	node->data = data;
	
	if(list != NULL)
	{
		node->next = list->head;
		list->head = node;
	}
}

void linked_list_append(LINKED_LIST list, void *data)
{
	LINKED_LIST_NODE iter;
	iter = list->head;
		
	LINKED_LIST_NODE tmp = (LINKED_LIST_NODE)malloc(sizeof(LINKED_LIST_NODE_t));
	tmp->data = data;
	
	if(iter == NULL)
	{
		tmp->next = list->head;
		list->head = tmp;
		return;
	}
	
	while(iter->next != NULL)
	{
		iter = iter->next;
	}
	
	iter->next = tmp;
	tmp->next = NULL;
}

// 0 5 15 20
void linked_list_insert(LINKED_LIST list, void *data, int idx)
{	
     LINKED_LIST_NODE node = (LINKED_LIST_NODE)malloc(sizeof(LINKED_LIST_NODE_t));
	node->data = data;
	
	int element = 1;
	LINKED_LIST_NODE iter = list->head;

	
	while(element < idx)
	{
		iter = iter->next;
		element++;
	}
	
	node->next = iter->next;
	iter->next = node;
}

void linked_list_set(LINKED_LIST list, void *data, int idx)
{
	int element = 0;
	LINKED_LIST_NODE iter = list->head;

	
	while(element < idx)
	{
		iter = iter->next;
		element++;
	}
	
	iter->data = data;
}

void *linked_list_get(LINKED_LIST list, int idx)
{
	int element = 0;
	LINKED_LIST_NODE iter = list->head;

	
	while(element < idx)
	{
		iter = iter->next;
		element++;
	}
	
	return iter->data;
}

// 0 5 10 15 20
void *linked_list_remove(LINKED_LIST list, int idx)
{
	int element = 0;
	LINKED_LIST_NODE iter = list->head;
    LINKED_LIST_NODE pre;
	
	while(element < idx)
	{
		pre = iter;
		iter = iter->next;
		element++;
	}
	
	pre->next = iter->next;
	void *data = iter->data;
	free(iter);
	
	return data;
}

void linked_list_removeall(LINKED_LIST list)
{
	LINKED_LIST_NODE iter = list->head;
	LINKED_LIST_NODE node = (LINKED_LIST_NODE)malloc(sizeof(LINKED_LIST_NODE_t));
	while(iter != NULL)
	{
		node = iter->next;
		free(iter);
		iter = node;
	}
}

void linked_list_concatenate(LINKED_LIST list, LINKED_LIST list2)
{
	LINKED_LIST_NODE iter = list->head;
	
	while(iter->next != NULL)
	{
		iter = iter->next;
	}
	
	iter->next = list2->head;
}
 // 0 5(tmp) 10(st) 15 20 30 40
LINKED_LIST linked_list_slice(LINKED_LIST list , int start , int end)
{
	LINKED_LIST_NODE iter = list->head;
	int element = 1;
	
	LINKED_LIST_NODE tmp = (LINKED_LIST_NODE)malloc(sizeof(LINKED_LIST_NODE_t));
	
	while(element < start)
	{
		iter = iter->next;
		element++;
	}
	tmp = iter;
	// elemet = 2
	LINKED_LIST st = (LINKED_LIST)malloc(sizeof(LINKED_LIST_t));
	st->head = iter->next;
	LINKED_LIST_NODE st2 = st->head;
	
	while(element < end)
	{
		iter = iter->next;
		st2 = st2->next;
		element++;
	}
	iter = iter->next;
	tmp->next = iter->next;
	st2->next = NULL;
	return st;
}

void linked_list_insert_piece(LINKED_LIST list, LINKED_LIST piece, int index)
{
	int element = 1;
	LINKED_LIST_NODE iter = list->head;
	LINKED_LIST_NODE tmp = (LINKED_LIST_NODE)malloc(sizeof(LINKED_LIST_NODE_t));
	
	while(element < index)
	{
		iter = iter->next;
		element++;
	}
	
	tmp = iter->next;
	iter->next = piece->head;
	
	LINKED_LIST_NODE final = (LINKED_LIST_NODE)malloc(sizeof(LINKED_LIST_NODE_t));
	final = piece->head;
	while(final->next != NULL)
	{
		final = final->next;
	}	
	
	final->next = tmp;
}
// 5 10 15(start) 20 25 30 35
void linked_list_trim(LINKED_LIST list, int left, int right) 
{
	int length = 0, element = 1;
	LINKED_LIST_NODE iter = list->head;
	LINKED_LIST_NODE tmp = (LINKED_LIST_NODE)malloc(sizeof(LINKED_LIST_NODE_t));
	LINKED_LIST_NODE start = (LINKED_LIST_NODE)malloc(sizeof(LINKED_LIST_NODE_t));
	
	while(iter != NULL)
	{
		iter = iter->next;
		length++;
	}
	iter = list->head;
	while(element < left)
	{
		iter = iter->next;
		element++;
	}
	start = iter->next;
	tmp = iter;
	
	while(left<(length - right))
	{
		iter = iter->next;
		start = start->next;
		left++;
	}
	tmp->next = iter->next;
	start = start->next;
	start->next = NULL;
}

void print_list(LINKED_LIST list)
{
	LINKED_LIST_NODE iter = list->head;
	while(iter != NULL)
	{
		printf("%d ", (iter->data));
		iter = iter->next;
	}
	
	printf("\n");
}

void main()
{
	LINKED_LIST list;
	list = linked_list_init();
	
	int a = 12;
	linked_list_append(list, a);
	a = 99;
	linked_list_append(list, a);
	a = 37;
	linked_list_append(list, a);
	a = 52;
	linked_list_append(list, a);
	a = 80;
	linked_list_append(list, a);
	a = 23;
	linked_list_append(list, a);
	
	printf("\nOriginal List : ");
	print_list(list);
	
	LINKED_LIST slice = linked_list_slice(list, 2, 4);
	printf("\nSliced Piece : ");
	print_list(slice);

	linked_list_insert_piece(list, slice, 1);
	printf("\nPiece Inserted List : ");
	print_list(list);
	
	linked_list_trim(list, 1, 2);
	printf("\nTrimmed List : ");
	print_list(list);
	
	linked_list_free(list);
	system("pause");
	return 0;
}
