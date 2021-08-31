#include <stdio.h>

// construct main method
int main() {
  // init variables
  double a = 10, b = 20, f;
  char ch;
  
  // test switch statement with '+'
  ch = '+';
  // print out current char operator
  printf("ch = %c\n", ch);
  // switch statement to check for operator
  // and then perform operation if possible
  // uses %g as formatter to remove trailing zeros
  switch (ch) {
    case '+':
        f = a + b;
        printf("f = %g\n", f);
        break;
    case '-':
        f = a - b;
        printf("f = %g\n", f);
        break;
    case '*':
        f = a * b;
        printf("f = %g\n", f);
        break;
    case '/':
        f = a / b;
        printf("f = %g\n", f);
        break;
    default:
        printf("invalid operator\n");
        break;
  }

  // test switch statement with '-'
  ch = '-';
  // print out current char operator
  printf("ch = %c\n", ch);
  // switch statement to check for operator
  // and then perform operation if possible
  // uses %g as formatter to remove trailing zeros
  switch (ch) {
    case '+':
        f = a + b;
        printf("f = %g\n", f);
        break;
    case '-':
        f = a - b;
        printf("f = %g\n", f);
        break;
    case '*':
        f = a * b;
        printf("f = %g\n", f);
        break;
    case '/':
        f = a / b;
        printf("f = %g\n", f);
        break;
    default:
        printf("invalid operator\n");
        break;
  }

  // test switch statement with '*'
  ch = '*';
  // print out current char operator
  printf("ch = %c\n", ch);
  // switch statement to check for operator
  // and then perform operation if possible
  // uses %g as formatter to remove trailing zeros
  switch (ch) {
    case '+':
        f = a + b;
        printf("f = %g\n", f);
        break;
    case '-':
        f = a - b;
        printf("f = %g\n", f);
        break;
    case '*':
        f = a * b;
        printf("f = %g\n", f);
        break;
    case '/':
        f = a / b;
        printf("f = %g\n", f);
        break;
    default:
        printf("invalid operator\n");
        break;
  }

  // test switch statement with '/'
  ch = '/';
  // print out current char operator
  printf("ch = %c\n", ch);
  // switch statement to check for operator
  // and then perform operation if possible
  // uses %g as formatter to remove trailing zeros
  switch (ch) {
    case '+':
        f = a + b;
        printf("f = %g\n", f);
        break;
    case '-':
        f = a - b;
        printf("f = %g\n", f);
        break;
    case '*':
        f = a * b;
        printf("f = %g\n", f);
        break;
    case '/':
        f = a / b;
        printf("f = %g\n", f);
        break;
    default:
        printf("invalid operator\n");
        break;
  }

  // test switch statement with invalid operator
  ch = '%';
  // print out current char operator
  printf("ch = %c\n", ch);
  // switch statement to check for operator
  // and then perform operation if possible
  // uses %g as formatter to remove trailing zeros
  switch (ch) {
    case '+':
        f = a + b;
        printf("f = %g\n", f);
        break;
    case '-':
        f = a - b;
        printf("f = %g\n", f);
        break;
    case '*':
        f = a * b;
        printf("f = %g\n", f);
        break;
    case '/':
        f = a / b;
        printf("f = %g\n", f);
        break;
    default:
        printf("invalid operator\n");
        break;
  }
}