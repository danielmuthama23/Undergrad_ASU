#include <stdio.h>

// construct main method
int main() {
  // init for-loop to run five times
  for (int i = 0; i < 5; i++) {
    // init variables
    double a = 10, b = 20, f;
    char ch;

    printf("Enter math operator: ");
    // get user input as char
    ch = getchar();
    // flush stdin to remove newline char
    fflush(stdin);

    // print user input operator
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
}