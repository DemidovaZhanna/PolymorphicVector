#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "interface.h"

#define INT 1
#define COMPLEX 2

const size_t MAXN = (1U << 31) - 1;

int main() {
    size_t n = 0;
    printf("Write down size of an array : ");
    char sn[100] = "";
    scanf("%s", sn);

    while (sn[0] == '-' || is_greater_than_max(sn, MAXN) || !is_num(sn)){
        if (sn[0] == '-') printf("\nERROR : Negative size. TRY AGAIN!\n\n");
        else if (!is_num(sn)) printf("\nERROR : It's not a number. TRY AGAIN\n\n");
        else printf("\nERROR : Too big size, choose less number <= %zu. TRY AGAIN\n\n", MAXN);
        printf("Write down size of an array : ");
        scanf("%s", sn);
    }

    n = convert_str_to_int(sn);

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
