// UCLA CS 111 Lab 1 command reading

#include "command.h"
#include "command-internals.h"
#include "alloc.h"    // For checked_malloc (), checked_realloc ()

#include <stdlib.h>   // For free ()
#include <stdio.h>    // For fprintf (), EOF
#include <ctype.h>    // For isalnum ()
#include <string.h>   // For strchr ()
// #include <stdbool.h>  // For booleans
#include <error.h>

/* Linked List node used for command_stream. command_stream is a
   linked-list stack implementation of "command"
   structs. I used the following link for reference on stacks:
   <https://www.cs.bu.edu/teaching/c/stack/linked-list/> */
   
struct command_node
{
  command_t command;
  struct command_node *next;
};

typedef struct command_node *command_node_t;

struct command_stream
{
  command_node_t *head;
};

/* To keep track of the line number, for error reports. */
int line_number = 1;

/* To make a pointer to the script input for
   helper functions to use */
void *script_file;
int (*get_next_byte) (void *);

/* For cases of whitespace following || && | #
   which are to be ignored. */
void
ignore_spaces ()
{
  int character = get_next_byte (script_file);
  if ( character != EOF )
    {
      while ( (character == '\n') || (character == '\t')
             || (character == ' ') )
        {
          if (character == '\n')
             {
               line_number++;
             }
          character = get_next_byte (script_file);
        }
      ungetc (character, script_file);
    }
}

/* Determine the command_type of the current command being interpreted */
enum command_type
determine_type (char *word)
{
  int cursor1 = get_next_byte (script_file);
  int cursor2 = get_next_byte (script_file);

  while(cursor1 != EOF)
    {
      if (cursor2 == '#' && !isspace(cursor1) )
        {
          error(1, 1, "%d: Invalid Syntax", line_number);
        }
      ungetc(d, script_file);
      // On comments, ignore entire rest of the line and skip to next command
      if (cursor1 == '#')
        {
          cursor2 = get_next_byte (script_file);
          while (cursor2 != '\n')
            {
              if (cursor2 == EOF)
                {
                  return SIMPLE_COMMAND;
                }
              cursor2 = get_next_byte (script_file);
            }
          return determine_type (word);
        }

      // For &, check for AND_COMMAND with matching & in next character.  
      else if (cursor1 == '&')
        {
          cursor2 = get_next_byte (script_file);
          if (cursor2 == '&')   // If it's an AND_COMMAND, we can ignore spaces.
            {
              ignore_spaces ();
              return AND_COMMAND;
            }
          else
            {
              error(1, 1, "%d: Invalid Syntax", line_number);
            }
        }

      // Inside subshell, we can ignore spaces and newlines
      else if (cursor1 == '(')
        {
          ignore_spaces ();
          return SUBSHELL_COMMAND;
        }

      else if (cursor1 == '|')
        {
          cursor2 = get_next_byte (script_file);
          if (cursor2 == '|')     // If it's an OR_COMMAND, we can ignore spaces
            {
              ignore_spaces ();
              return OR_COMMAND;
            }

          // If it's a PIPE_COMMAND, we can also ignore spaces
          else if ( (isalnum(cursor2)) || (isspace(cursor2))
                     || cursor2 == '+' || cursor2 == ',' || cursor2 == '-'
                   || cursor2 == '.' || cursor2 == '/' || cursor2 == ':'
                     || cursor2 == '@' || cursor2 == '^' || cursor2 == '_'
                   || cursor2 == '!' || cursor2 == '%' )
            {
              ungetc(cursor2, script_file);
              ignore_spaces ();
              return PIPE_COMMAND;
            }
          else if (cursor2 == EOF)
            {
              error(1, 1, "%d: Invalid Syntax", line_number);
            }
        }

      else if (cursor1 == '\n')
        {
          line_number++;
        }

      else if (cursor1 == ';' || cursor1 == ')' || cursor1 == EOF)
        {
          if (cursor1 == ')')
            {
              ungetc(cursor1, script_file);
            }
          return SIMPLE_COMMAND;
        }
      word[strlen(word)] = cursor1;
    }
  return SEQUENCE_COMMAND;
}

// Creates a command with the string in word
command_t
create_command (char *word)
{
  if(strlen(buffer) == 0)
    {
      error(1, 1, "%d: Invalid Syntax", line_number);
    }
  command_t command = checked_malloc ( sizeof(struct command) );
  command->type = SIMPLE_COMMAND;
  command->status = -1;
  command->input = NULL;
  command->output = NULL;
  command->u.word = checked_malloc ( sizeof(char*) );
  size_t max_word_length = 8;
  size_t input_length = 0;
  size_t output_length = 0;
  size_t current_word_length = 0;
  size_t index = 0;
  bool in_word = false;
  bool in_input = false;
  bool in_output = false;
  bool input = false;
  bool output = false;
  int i;
  for (int i = 0; word[i]; i++)
    {
      if ( word[i] == '<')
        {
          if (i == 0 || input || output
              || in_input || in_output)
            {
              error(1, 1, "%d: Invalid Syntax", line_number);
            }
          else
            {
              command->input = checked_realloc (command->input, input_length + 1);
              in_input = true;
            }
        }
      else if ( word[i] == '>')
        {
          if (i == 0 || output || in_output)
            {
              error(1, 1, "%d: Invalid Syntax", line_number);
            }
          command->output = checked_realloc (command->output, output_length + 1);
        }
      else if ( isalnum(word[i]) || strchr("!%+,-./:@^_", word[i]) ) )
        if (in_input)
          {
            input = true;
          }
        else if (in_output)
          {
            output = true;
          }
        else if (!in_word)
          {
            if ( (input || output) && !in_input && !in_input )
              {
                error(1, 1, "%d: Invalid Syntax", line_number);
              }
            if ( index >= max_word_length)
              {
                checked_realloc (command->u.word, &max_word_length);
              }
            command->u.word[index] = checked_malloc (8*sizeof(char));
            current_word_length = 8;
            command->u.word[index][0] = buffer[i];
            in_word = true;
          }

    }
}

/* I read the following source: <http://www.newty.de/fpt/fpt.html> to get
   a better understanding of function pointers, since I have only seen
   examples of them before, but never worked with them myself. */
command_stream_t
make_command_stream (int (*get_next_byte) (void *),
                     void *get_next_byte_argument)
{
  return 0;
}

command_t
read_command_stream (command_stream_t s)
{
  /* FIXME: Replace this with your implementation too.  */

  /* Read a command from STREAM; return it, or NULL on EOF.  If there is
     an error, report the error and exit instead of returning.  */  

  error (1, 0, "command reading not yet implemented");
  return 0;
}


/*


void
push (char *word, stack_t *stream_top)
{
  stack_t new_word;
  new_word = (stack_t) malloc (sizeof (stack) );
  if (new_word == NULL)   // malloc error check
    {
      fprintf(stderr, "Failed to allocate memory with malloc.\n", );
      exit(1);
    }
  new_word->word = word;
  new_word->next = *stream_top;
  *stream_top = new_word;
}

void
pop (stack_t *stream_top)
{
  if (*stream_top == NULL)
    {
      printf ("**Nothing to POP!\n");
    }
    
  else
    {
      stack_t new_top;
      new_top = (*stream_top)->next;
      printf ("**POPPED %s!\n", (*stream_top)->word);
      free (*stream_top);
      *stream_top = new_top;
    }
    
}

void
print_stack (stack_t stream_top)
{
  stack *cursor = stream_top;
  if (cursor == NULL)
    {
      printf ("**PRINTING...\n   Stack empty!\n");
    }
  
  else
    {
      printf ("**PRINTING...\n   Stack contains: ");
      while (cursor != NULL)
        {
          printf ("%s ", cursor->word);
          cursor = cursor->next;
        }
      printf ("\n");
    }
}

void
print_stream_top (stack *stream_top)
{
  stack *cursor = stream_top;
  if (cursor == NULL)
    {
      printf ("   Top of stack: <Stack empty!>\n");
    }
  
  else
    {
      printf ("   Top of stack: %s\n", stream_top->word);
    }
}

void
push_n_print (char *word, stack_t *stream_top)
{
  push (word, stream_top);
  print_stack (*stream_top);
  print_stream_top (*stream_top);
}
*/
