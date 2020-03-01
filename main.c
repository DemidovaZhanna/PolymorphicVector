#include <stdio.h>
#include "general_fun.h"
#include "interface_vectorD.h"
#include "interface_vectorC.h"

const int MAXN = (1U << 31) - 1;

int main() {
    int n = 0;
    printf("Write down size of an array : ");
    char sn[100] = "";
    scanf("%s", sn);

    while (sn[0] == '-' || is_greater_than_max(sn, MAXN)){
        if (sn[0] == '-') printf("\nERROR : Negative size. TRY AGAIN!\n\n");
        else printf("\nERROR : Too big size, choose less number <= %i. TRY AGAIN\n\n", MAXN);
        printf("Write down size of an array : ");
        scanf("%s", sn);
    }

    n = convert_str_to_int(sn);

    char s[100] = "";

    printf("Do you want array of real or complex numbers?\nType \"Real\" or \"Complex\" : ");
    while (scanf("%s", s)) {
        if (!strcmp(s, "Real")) { interface_vectorD(n); break; }
        else if (!strcmp(s, "Complex")) { interface_vectorC(n); break; }
        else printf("\nERROR : Invalid keyword. TRY AGAIN.\n\n");
    }

    return 0;
}
