#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int option;
    char *str1 = NULL;
    char *str2 = NULL;

    while ((option = getopt(argc, argv, "a:b:")) != -1) {
        switch (option) {
            case 'a':
                str1 = optarg;
                break;
            case 'b':
                str2 = optarg;
                break;
            default:
                printf("Usage: %s -a <string1> -b <string2>\n", argv[0]);
                return 1;
        }
    }

    if (str1 == NULL || str2 == NULL) {
        printf("Both -a and -b options are required.\n");
        return 1;
    }
    printf("A is %c and B is %c\n", str1[0], str2[0]);
    
    return 0;
}
