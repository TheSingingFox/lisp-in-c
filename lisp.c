#include <stdio.h>
#include <string.h>

/* Declare a buffer for user input of size 2048 */
static char input[2048];

int main(int argc, char** argv) {

  /* Print Version and Exit Information */
  puts("foxlisp Version 0.0.0.0.2");
  puts("Type (exit) to exit\n");

  /* In a never ending loop */
  for(int stay = 1; stay;) {

    /* Output our prompt */
    fputs("foxlisp> ", stdout);

    /* Read a line of user input of maximum size 2048 */
    fgets(input, 2048, stdin);

    if(!strncmp(input, "(exit)", 6)) {
      stay = 0;
    } else {
      /* Echo input back to user */
      printf("%s", input);
    }
  }

  return 0;
}
