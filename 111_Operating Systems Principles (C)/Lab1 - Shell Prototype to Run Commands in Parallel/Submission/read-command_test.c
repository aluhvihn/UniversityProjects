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

command_t
create_command(char *word)
{
  if(!strlen(word))
    {
      error(1, 1, "%d: Invalid Syntax", line_number);
    }
  command_t command = checked_malloc(sizeof(struct command));
  command->type = SIMPLE_COMMAND;
  command->status = -1;
  command->input = NULL;
  command->output = NULL;
  command->u.word = checked_malloc(8*sizeof(char*));
  size_t word_size = 8;
  size_t input_size = 8;
  size_t output_size = 8;      
  size_t cur_word_size; 
  size_t index = 0;
  bool in_word = false;
  bool in_input = false;
  bool in_output = false;
  bool input = false;
  bool output = false;
  int i;
  for(i = 0; word[i]; i++)
  {
    if(word[i] == '<')
    {
      if(i == 0 || input || output 
        || in_input || in_output)
        {
          error(1, 1, "%d: Invalid Syntax", line_number);
        }
      command->input = checked_malloc(8*sizeof(char));
      in_input = true;
    }
    else if(word[i] == '>')
    {
      if(i == 0 || output || in_output)
        {
          error(1, 1, "%d: Invalid Syntax", line_number);
        }
      command->output = checked_malloc(8*sizeof(char)); 
      in_input = false;
      in_output = true;
    }
    else if(isalnum(word[i]) || strchr("!%+,-./:@^_", word[i]))
    {
      if(in_input)
      {
        input = true;
        char* string = command->input;
        if(strlen(string) >= input_size)
          checked_grow_alloc(string, &input_size);
        string[strlen(string)] = word[i];
      }
      else if(in_output)
      {
        output = true;
        char* string = command->output;
        if(strlen(string) >= output_size)
          checked_grow_alloc(string, &output_size);
        string[strlen(string)] = word[i];
      }
      else if(!in_word)
      {
        if( (input || output) && !in_input && !in_output)
          {
            error(1, 1, "%d: Invalid Syntax", line_number);
          }
        if(index >= word_size)
          checked_grow_alloc(command->u.word, &word_size);
        command->u.word[index] = checked_malloc(8*sizeof(char));
        cur_word_size = 8;
        command->u.word[index][0] = word[i];
        in_word = true;
      }
      else if(in_word)
      {
        char *string = command->u.word[index];
        if(strlen(string) >= cur_word_size)
          checked_grow_alloc(string, &cur_word_size);
        string[strlen(string)] = word[i];
      }
    }
    else if(strchr("\t ", word[i]))
    {
      if(in_word)
      {
        in_word = false;
        index++;
      }
      else if(input && in_input)
        in_input = false;
      else if(output && in_output)
        in_output = false; 
    }
    else if(word[i] == EOF)
    {
      if(index >= word_size)
        checked_grow_alloc(command->u.word, &word_size);
      return command;
    }
    else
      {
        error(1, 1, "%d: Invalid Syntax", line_number);
      }
  }
  memset((void *) word, '\0', 1024);
  if(index >= word_size)
        checked_grow_alloc(command->u.word, &word_size);
  return command;
}

command_t
combine_command(char *word, enum command_type type, command_t caller)
{
  command_t compound_command = checked_malloc(sizeof(struct command));
  compound_command->type = type;
  compound_command->status = -1;
  if(caller == NULL)
    compound_command->u.command[0] = create_command(word);
  else if(caller->type == SUBSHELL_COMMAND || (type != PIPE_COMMAND && caller->type == PIPE_COMMAND) || (type == PIPE_COMMAND) == (caller->type == PIPE_COMMAND))
    compound_command->u.command[0] = caller;
  else if(type == PIPE_COMMAND && caller->type != PIPE_COMMAND)
    compound_command->u.command[0] = caller->u.command[1];
  enum command_type adjacent_type = scan(word);
  if(adjacent_type == SIMPLE_COMMAND || adjacent_type == SEQUENCE_COMMAND)
  {
    compound_command->u.command[1] = create_command(word);
    return compound_command;
  }
  else if(adjacent_type == SUBSHELL_COMMAND)
  {
    command_t subshell = make_subshell_command(word);
    adjacent_type = scan(word);
    if(adjacent_type == SIMPLE_COMMAND)
    {
      compound_command->u.command[1] = subshell;
      return compound_command;
    }
    else if(type != PIPE_COMMAND && adjacent_type == PIPE_COMMAND)
    {
      compound_command->u.command[1] = subshell;
      compound_command->u.command[1] = combine_command(word, adjacent_type, compound_command);
      return compound_command;
    }
    else
    {
      compound_command->u.command[1] = subshell;
      command_t adjacent_command = combine_command(word, adjacent_type, compound_command);
      return adjacent_command;
    }
  }
  else if(type != PIPE_COMMAND && adjacent_type == PIPE_COMMAND)
  {
    compound_command->u.command[1] = create_command(word);
    compound_command->u.command[1] = combine_command(word, adjacent_type, compound_command);
    return compound_command;
  }
  else
  {
    compound_command->u.command[1] = create_command(word);
    command_t adjacent_command = combine_command(word, adjacent_type, compound_command);
    return adjacent_command;
  }
}

command_t
make_subshell_command(char *word)
{
  command_t subshell = checked_malloc(sizeof(struct command));
  subshell->type = SUBSHELL_COMMAND; subshell->status = -1;
  enum command_type type = scan(word);
  command_t command = make_command(word, type);
  eat_whitespace();
  char c;
  if((c = get_byte(get_byte_argument)) == ')')
  {
    subshell->u.subshell_command = command;
    return subshell;
  }
  else
  {
    ungetc(c, get_byte_argument);
    command_t top = checked_malloc(sizeof(struct command)); 
    top->type = SEQUENCE_COMMAND; top->status = -1;
    top->u.command[0] = command; top->u.command[1] = NULL;
    while((c = get_byte(get_byte_argument)) != ')')
    {
      ungetc(c,get_byte_argument);
      enum command_type type = scan(word);

      command_t new_sequence = checked_malloc(sizeof(struct command));
      new_sequence->type = SEQUENCE_COMMAND; new_sequence->status = -1;
      new_sequence->u.command[0] = make_command(word, type);
      new_sequence->u.command[1] = NULL;
      command_t bottom = top;
      while(bottom->u.command[1] != NULL)
        bottom = bottom->u.command[1];
      bottom->u.command[1] = new_sequence;
    }
    command_t bottom = top;
    while(bottom->u.command[1]->u.command[1] != NULL)
      bottom = bottom->u.command[1];
    bottom->u.command[1] = bottom->u.command[1]->u.command[0];
    subshell->u.subshell_command = top;
    return subshell;
  }
}

command_t
make_command(char* word, enum command_type type)
{
  if(type == SIMPLE_COMMAND)
    return create_command(word);
  else if(type == SUBSHELL_COMMAND)
  {
    command_t subshell = make_subshell_command(word);
    type = scan(word);
    if(type == SIMPLE_COMMAND)
      return subshell;
    else
      return combine_command(word, type, subshell);
  }
  else
    return combine_command(word, type, NULL);
}

command_node_t
make_node(char* word, enum command_type type)
{
  command_node_t node = checked_malloc(sizeof(struct  command_node));
  node->next = NULL;
  node->command = make_command(word,type);
  return node;
}

command_stream_t
make_command_stream (int (*get_next_byte) (void *),
         void *get_next_byte_argument)
{
  line_count = 1;
  char word[1024] = "";
  get_byte = get_next_byte;
  get_byte_argument = get_next_byte_argument;
  command_stream_t stream = checked_malloc(sizeof(struct command_stream));
  command_node_t node = checked_malloc(sizeof(struct command_node));
  command_node_t temp_node = node;
  command_node_t head = NULL;    
  command_node_t tail = NULL;
  if(!feof(get_byte_argument))
  {
    eat_whitespace();
    if((word[0] = get_byte(get_byte_argument)) == EOF)
    {
      free(stream);
      free(node);
      return NULL;
    }
    ungetc(word[0], get_byte_argument);
    word[0] = '\0';
    enum command_type type = scan(word);  

    while(1)  
    {
      if(type == SEQUENCE_COMMAND)
        temp_node = make_node(word, SIMPLE_COMMAND);
      else
        temp_node = make_node(word, type);  
      if(!head)
      {
        head = temp_node;
      }
      else
      {
        tail->next = temp_node;
        temp_node->prev = tail;
      }
      tail = temp_node;
      if(type == SEQUENCE_COMMAND)
        break;
      eat_whitespace();
      if((word[0] = get_byte(get_byte_argument)) == EOF)
      {
        stream->commands = &head;
        return stream;
      }
      ungetc(word[0], get_byte_argument);
      word[0] = '\0';
      type = scan(word);
    }
  }
  stream->commands = &head;
  return stream;
}

command_t
read_command_stream (command_stream_t s)
{
  if(s == NULL)
    return NULL;
  if(*(s->commands) != NULL)
  {
    command_node_t stream = *(s->commands);
    *(s->commands) = stream->next;
    if(stream->prev != NULL)
    {
      free(stream->prev->command);
      free(stream->prev);
    }
    return stream->command;
  }
  return NULL;
}
