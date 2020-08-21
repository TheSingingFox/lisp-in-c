#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <editline/readline.h>

int main(int argc, char** argv) {

  /* Print Version and Exit Information */
  puts("foxlisp Version 0.0.0.0.3");
  puts("Type (exit) to exit\n");

  /* In a never ending loop */
  for(int stay = 1; stay;) {

    /* Output our prompt and get input */
    char *input = readline("foxlisp> ");

    /* Add input to history */
    add_history(input);

    /* Create an exit condition */
    if(!strncmp(input, "(exit)", 6)) {
      stay = 0;
    } else {
      /* Echo input back to user */
      printf("%s\n", input);
    }

    /* Free retrieved input */
    free(input);
  }

  return 0;
}
