#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* If we are compiling on Windows compile these functions */
#ifdef _WIN32

static char buffer[2048];

/* Fake readline function */
char *readline(char *prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char *cpy = malloc(strlen(buffer) + 1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy) - 1] = '\0';

  return cpy;
}

/* Fake add_history function */
void add_history(char *unused) {}

/* Otherwise include the editline header */
#else

#include <editline/readline.h>

#endif

int main(int argc, char** argv) {

  /* Print Version and Exit Information */
  puts("foxlisp Version 0.0.0.0.4\nCreated by Silas Vedder");
  puts("Type (help) for help and (exit) to exit\n");

  /* In a never ending loop */
  for(int stay = 1; stay;) {

    /* Output our prompt and get input */
    char *input = readline("foxlisp> ");

    /* Add input to history */
    add_history(input);

    /* Create an exit condition */
    if(!strncmp(input, "(exit)", 6)) {
      stay = 0;
    } else if(!strncmp(input, "(help)", 6)) {
      printf("There isn't much you can do yet.\n");
      printf("To be honest, the only thing you /can/ do is view this help and exit.\n");
      printf("Everything else will just get printed back to you.\n");
    } else {
      /* Echo input back to user */
      printf("%s\n", input);
    }

    /* Free retrieved input */
    free(input);
  }

  return 0;
}
