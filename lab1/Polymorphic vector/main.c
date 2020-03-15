#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "interface.h"


const size_t MAXN = (1U << (sizeof(int) * 8 - 1)) - 1;

int main() {
    printf("Write down size of an array : ");

    size_t n = read_correct_num(0);
    char s[100] = "";

    printf("Choose type of your vector :\n"
           "1. Integer\n"
           "2. Complex\n");

    while (scanf("%s", s)) {
        if (!strcmp(s, "Integer") || !strcmp(s, "1")) { interface(n, INT); break; }
        else if (!strcmp(s, "Complex") || !strcmp(s, "2")) { interface(n, COMPLEX); break; }
        else printf("\nERROR : Invalid keyword. TRY AGAIN.\n\n");
        printf("Choose type of your vector :\n"
               "1. Integer\n"
               "2. Complex\n");
    }

    return 0;
}
