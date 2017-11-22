#include <stdio.h>
#include <stdlib.h>

/* My implementation of a stack, using
   <https://www.cs.bu.edu/teaching/c/stack/linked-list/>
   <http://www.learn-c.org/en/Linked_lists>
   for reference */

typedef struct node {
    int val;
    struct node * next;
} node_t;

void push(node_t ** head, int val) {
    node_t * new_node;
    new_node = (node_t *)malloc(sizeof(node_t));
    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
}

void pop(node_t ** head) {
    if (*head == NULL) {
        printf("Nothing to pop!\n");
    }
    
    
    else {
        node_t *next_node;
        next_node = (*head)->next;
        printf("Popped %d!\n", (*head)->val);
        free(*head);
        *head = next_node;
    }
    
}

void print_list(node_t * head) {
    node_t * current = head;

	if (current == NULL)
	{
		printf("List Empty!\n");
	}
	
    else
    {
    	printf("List contains: ");
    	while (current != NULL) {
        	printf("%d ", current->val);
        	current = current->next;
    	}
    	printf("\n");
    }
}

void print_top(node_t * head) {
    node_t * current = head;

	if (current == NULL)
	{
		printf("List Empty!\n");
	}
	
    else
    {
    	printf("Top of the list is: %d\n", head->val);
    }
}

int main(void) {
	// node_t *My_list = (node_t *)malloc(sizeof(node_t));
	node_t *My_list;
	print_list(My_list);
	pop(&My_list);
	int i;
	for (i=10; i>=0; i--)
	{
		push(&My_list,i);
		print_list(My_list);
	}
	
	for (i=10; i>=-2; i--)
	{
		print_top(My_list);
		pop(&My_list);
	}
	return 0;
}
