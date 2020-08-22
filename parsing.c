#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mpc.h"

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

  /* Create parsers */
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Foxlisp = mpc_new("foxlisp");

  /* Defining the parsers */
  mpca_lang(MPCA_LANG_DEFAULT,
	    "                                                   \
             number   : /-?[0-9]+/;                             \
             operator : '+' | '-' | '*' | '/';                  \
             expr     : <number> | '(' <operator> <expr>+ ')';  \
             foxlisp  : /^/ <operator> <expr>+ /$/;             \
            ",
	    Number, Operator, Expr, Foxlisp);

  /* Print Version and Exit Information */
  puts("foxlisp Version 0.0.0.0.5\nCreated by Silas Vedder");
  puts("Press C-c to exit\n");

  /* In a never ending loop */
  for(int stay = 1; stay;) {

    /* Output our prompt and get input */
    char *input = readline("foxlisp> ");

    /* Add input to history */
    add_history(input);

    /* Attempt to parse user input */
    mpc_result_t r;
    if(mpc_parse("<stdin>", input, Foxlisp, &r)) {
      /* On success print the AST */
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      /* Otherwise print the error */
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    /* Free retrieved input */
    free(input);
  }

  /* Undefine and delete parsers */

  return 0;
}
