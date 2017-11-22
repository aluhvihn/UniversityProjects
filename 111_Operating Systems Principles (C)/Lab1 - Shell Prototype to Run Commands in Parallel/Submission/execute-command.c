// UCLA CS 111 Lab 1 command execution

#include "command.h"
#include "command-internals.h"

#include <error.h>

/* Return the exit status of a command, which must have previously
   been executed.  Wait for the command, if it is not already finished.  */
int
command_status (command_t c)
{
  return c->status;
}

/* Execute a command.  Use "time travel" if the flag is set.  */
void
execute_command (command_t c, bool time_travel)
{
  /* FIXME: Replace this with your implementation.  You may need to
     add auxiliary functions and otherwise modify the source code.
     You can also use external functions defined in the GNU C Library.  */
  error (1, 0, "command execution not yet implemented");
}
