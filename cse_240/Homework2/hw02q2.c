#include <stdio.h>

// the four defined macros based off the four given functions
#define subm(a, b) a - b
#define cubem(a) a * a * a
#define distancem(a, b) a > b ? a - b : b - a
#define maxm(a, b) a > b ? a : b

// the four given functions are defined below
int subf(int a, int b) {
    return a - b;
}

int cubef(int a) {
    return a * a * a;
}

int distancef(int a, int b) {
    return a > b ? a - b : b - a;
}

int maxf(int a, int b) {
    return a > b ? a : b;
}

// define the main function
int main() {
    // init int a and b
    int a = 7, b = 2;

    // test subtraction function and macro
    printf("subf(a, b) = %i\n", subf(a, b));
    printf("subm(a, b) = %i\n", subm(a, b));
    printf("subf(a++, b--) = %i\n", subf(a++, b--));
    a = 7; b = 2; // reset a, b values (this is repeated after every increment/decrement)
    printf("subm(a++, b--) = %i\n", subm(a++, b--));

    // test cube function and macro
    a = 7; b = 2;
    printf("cubef(a) = %i\n", cubef(a));
    printf("cubem(a) = %i\n", cubem(a));
    printf("cubef(--a) = %i\n", cubef(--a));
    a = 7; b = 2;
    printf("cubem(--a) = %i\n", cubem(--a));

    // test distance function and macro
    a = 7; b = 2;
    printf("distancef(a, b) = %i\n", distancef(a, b));
    printf("distancem(a, b) = %i\n", distancem(a, b));
    printf("distancef(--a, --b) = %i\n", distancef(--a, --b));
    a = 7; b = 2;
    printf("distancem(--a, --b) = %i\n", distancem(--a, --b));

    // test max function and macro
    a = 7; b = 2;
    printf("maxf(a, b) = %i\n", maxf(a, b));
    printf("maxm(a, b) = %i\n", maxm(a, b));
    printf("maxf(a++, b) = %i\n", maxf(a++, b));
    a = 7; b = 2;
    printf("maxm(a++, b) = %i\n", maxm(a++, b));

    return 0;
}
