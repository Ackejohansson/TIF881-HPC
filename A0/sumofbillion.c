#include <stdio.h>

int main() {
    long long int sum = 0;
    int billion = 1000000000;

    for (int i = 0; i < billion; i++){
        sum += i;
    }
    fprintf(stdout, "%lld\n", sum);
    return 0;
}
