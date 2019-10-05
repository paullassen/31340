#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

/* Read a string, and return a pointer to it.  Returns NULL on EOF.
 * Taken from the readline manual (info readline). 
 */
char *rl_gets (char *prompt)
{
  /* A static variable for holding the line. */
  static char *line_read = (char *)NULL;

  /* If the buffer has already been allocated, return the memory
     to the free pool. */
  if (line_read) {
      free(line_read);
      line_read = (char *)NULL;
    }
      
  /* Get a line from the user. */
  line_read = readline(prompt);
      
  /* If the line has any text in it, save it on the history. */
  if (line_read && *line_read)  add_history (line_read);
  
  return line_read;
}


int main()
{
  char *input;

  while ((input = rl_gets("Welcome> "))) {

    if (strcmp(input, "help") == 0) {

      puts("Valid commands are:\n\thelp\n\tquit || exit\n");

    } else if ((strcmp(input, "quit") == 0) ||
	       (strcmp(input, "exit") == 0)) {

      break;

    } else if (*input) {

      puts("Sorry, I don't know how to do that");

    }
  }

  puts("Bye!");
  return 0;
}
/*
 *  bash-2.05a$ ./p11
 *  Welcome> hello
 *  Sorry, I don't know how to do that
 *  Welcome> help
 *  Yes, you're going to need it!
 *  Welcome> quit
 *  Bye!
 *  bash-2.05a$
 */
