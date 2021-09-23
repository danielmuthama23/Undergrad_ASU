#include <stdio.h>
#include <string.h>

int main() {
    char arr[10] = "hello";

    char* p = &arr[0];

    printf("%c\n", *(p + 4));

    return 0;
}