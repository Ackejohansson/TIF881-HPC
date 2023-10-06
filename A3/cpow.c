#include <stdio.h>
#include <complex.h>

int main() {
    double complex x = -2.0 + 2.0 * I;

    double complex result = cpow(x, 2) - 1.0;

    printf("Result: %f + %fi\n", creal(result), cimag(result));

    return 0;
}
