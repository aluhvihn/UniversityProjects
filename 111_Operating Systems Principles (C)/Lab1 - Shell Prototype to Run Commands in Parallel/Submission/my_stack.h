/* My implementation of a stack, using
   <https://www.cs.bu.edu/teaching/c/stack/linked-list/>
   for reference */

// Linked-list implementation for stack
typedef struct stack
{
  struct stack *next;
  char *word;
} stack;

typedef stack *stack_t;

// Add a command to the top of the stack
void push (char *word, stack_t *stack_top);

// Remove the topmost command from the stack
void pop (stack_t *stack_top);