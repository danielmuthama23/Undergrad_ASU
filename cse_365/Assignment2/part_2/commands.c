#include <stdio.h>

int main(int argc, char* argv[]) {
    argc--; // decrement to get correct arg length
    printf("%d\n", argc);

    if (argc == 0) return 0;

    for (int i = argc; i > 0; i--) {
        printf("%s ", argv[i]);
    }

    printf("\n");
    return 0;
}
