#include <stdio.h>

int main(void) {
    int  n = 5;
    long suma = 0;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0) continue;
        suma += i;
    }
    const char *msg = "int for while return";
    printf("suma = %ld\n", suma);
    return 0;
}
