#include <stdio.h>
int main(){
    int size = 600000;

    int as[size];
    for (int ix = 0; ix < size; ++ix )
        as[ix] = 0;

    printf("%d\n", as[0]);
    return 0;
}