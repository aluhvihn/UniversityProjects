// UCLA CS 111 Lab 1 command reading
#include "alloc.h"
#include "command.h"
#include "command-internals.h"

#include <error.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int line_number;
int (*get_byte) (void *);
void *get_byte_argument;
command_t make_command(char* word, enum command_type type);
command_t make_subshell_command(char* word);

typedef struct command_node *command_node_t;

struct command_node
{
  command_t command;
  command_node_t next;
  command_node_t prev;
};

struct command_stream
{
  command_node_t* commands;
};

void
syntax_error()
{
  error(1, 0, "%d: Invalid Syntax", line_number);
}

void 
ignore_spaces()
{
  if(!feof(get_byte_argument))
  {
    char c = get_byte(get_byte_argument);
    while(strchr("\n\t ", c))
    {
      if(c == '\n')
        line_number++;
      c = get_byte(get_byte_argument);
    }
    ungetc(c, get_byte_argument);
  }
}

enum command_type
scan(char *word)
{
  while(!feof(get_byte_argument))
  { 
    char c = get_byte(get_byte_argument);
    char d = get_byte(get_byte_argument);
    if(d == '#' && !strchr("\n\t ", c))
      syntax_error();
    ungetc(d, get_byte_argument);
    switch(c)
    {
      case '#':
        d = get_byte(get_byte_argument);
        while(d != '\n')
        {
            if(d == EOF)
              return SIMPLE_COMMAND;
            d = get_byte(get_byte_argument);
        }
        return scan(word);
      case '&':
        d = get_byte(get_byte_argument);
        if(d == '&')
        {
          ignore_spaces();
          return AND_COMMAND;
        }
        else if(d == EOF)
          syntax_error();
        else 
          ungetc(d, get_byte_argument);
        break;
      case '(':
      {
        ignore_spaces();
        return SUBSHELL_COMMAND;
      }
      case ')':
      {
        ungetc(c, get_byte_argument);
        return SIMPLE_COMMAND;
      }
      case '|':
        d = get_byte(get_byte_argument);
        if(d == '|')
        {
          ignore_spaces();
          return OR_COMMAND;
        }
        else if(isalnum(d) || strchr("!%+,-./:@^_\t\n ", d))
        {
          ungetc(d, get_byte_argument);
          ignore_spaces();
          return PIPE_COMMAND;
        }
        else if(d == EOF)
          syntax_error();
      case '\n': line_number++;
      case ';':
      case EOF:
        return SIMPLE_COMMAND;
    }
    word[strlen(word)] = c;
  }
  return SEQUENCE_COMMAND;
}

command_t
make_simple_command(char *word)
{
  if(!strlen(word))
    syntax_error();
  command_t command = checked_malloc(sizeof(struct command));
  command->type = SIMPLE_COMMAND; command->status = -1;
  command->input = NULL; command->output = NULL;
  command->u.word = checked_malloc(8*sizeof(char*)); size_t max_word_length = 8;
  size_t input_length = 8;size_t output_length = 8;      
  size_t current_word_length; size_t index = 0; bool in_word = false;
  bool in_input = false; bool in_output = false;
  bool input = false; bool output = false; int i;
  for(i = 0; word[i]; i++)
  {
    if(word[i] == '<')
    {
      if(i == 0 || input || output 
        || in_input || in_output)
        syntax_error();
      command->input = checked_malloc(8*sizeof(char));
      in_input = true;
    }
    else if(word[i] == '>')
    {
      if(i == 0 || output || in_output)
        syntax_error();
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
        if(strlen(string) >= input_length)
          checked_grow_alloc(string, &input_length);
        string[strlen(string)] = word[i];
      }
      else if(in_output)
      {
        output = true;
        char* string = command->output;
        if(strlen(string) >= output_length)
          checked_grow_alloc(string, &output_length);
        string[strlen(string)] = word[i];
      }
      else if(!in_word)
      {
        if((input || output) && !in_input && !in_output)
          syntax_error();
        if(index >= max_word_length)
          checked_grow_alloc(command->u.word, &max_word_length);
        command->u.word[index] = checked_malloc(8*sizeof(char));
        current_word_length = 8;
        command->u.word[index][0] = word[i];
        in_word = true;
      }
      else if(in_word)
      {
        char *string = command->u.word[index];
        if(strlen(string) >= current_word_length)
          checked_grow_alloc(string, &current_word_length);
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
      if(index >= max_word_length)
        checked_grow_alloc(command->u.word, &max_word_length);
      return command;
    }
    else
      syntax_error();
  }
  memset((void *) word, '\0', 1024);
  if(index >= max_word_length)
        checked_grow_alloc(command->u.word, &max_word_length);
  return command;
}

command_t
make_compound_command(char *word, enum command_type type, command_t caller)
{
  command_t compound_command = checked_malloc(sizeof(struct command));
  compound_command->type = type; compound_command->status = -1;
  if(caller == NULL)
    compound_command->u.command[0] = make_simple_command(word);
  else if(caller->type == SUBSHELL_COMMAND || (type != PIPE_COMMAND && caller->type == PIPE_COMMAND) || (type == PIPE_COMMAND) == (caller->type == PIPE_COMMAND))
    compound_command->u.command[0] = caller;
  else if(type == PIPE_COMMAND && caller->type != PIPE_COMMAND)
    compound_command->u.command[0] = caller->u.command[1];
  enum command_type adjacent_type = scan(word);
  if(adjacent_type == SIMPLE_COMMAND || adjacent_type == SEQUENCE_COMMAND)
  {
    compound_command->u.command[1] = make_simple_command(word);
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
      compound_command->u.command[1] = make_compound_command(word, adjacent_type, compound_command);
      return compound_command;
    }
    else
    {
      compound_command->u.command[1] = subshell;
      command_t adjacent_command = make_compound_command(word, adjacent_type, compound_command);
      return adjacent_command;
    }
  }
  else if(type != PIPE_COMMAND && adjacent_type == PIPE_COMMAND)
  {
    compound_command->u.command[1] = make_simple_command(word);
    compound_command->u.command[1] = make_compound_command(word, adjacent_type, compound_command);
    return compound_command;
  }
  else
  {
    compound_command->u.command[1] = make_simple_command(word);
    command_t adjacent_command = make_compound_command(word, adjacent_type, compound_command);
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
  ignore_spaces();
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
    return make_simple_command(word);
  else if(type == SUBSHELL_COMMAND)
  {
    command_t subshell = make_subshell_command(word);
    type = scan(word);
    if(type == SIMPLE_COMMAND)
      return subshell;
    else
      return make_compound_command(word, type, subshell);
  }
  else
    return make_compound_command(word, type, NULL);
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
  line_number = 1;
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
    ignore_spaces();
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
      ignore_spaces();
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
Status API Training Shop Blog About
© 2015 GitHub, Inc. Terms Privacy Security Contact
