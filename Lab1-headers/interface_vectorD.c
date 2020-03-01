//
// Created by Vasiliy Evdokimov on 28.02.2020.
//

#include "interface_vectorD.h"
#include "general_fun.h"
#include <string.h>

const int MAXN;

void interface_vectorD(int n) {
    vectorD vd = make_vd(n);
    printf("Enter %i real numbers : ", n);
    n = vd.size;
    for (int i = 0; i < n; ++i) scanf("%lf", vd.p + i);

    outputD(&vd);

    printf("\nWhat do you want to do with your vector?\n");
    printf("Choose number of option to apply to your elements :\n");
    printf("1. Add 1\n2. Sub 1\n3. Abs\n4. Elements greater than 0\n5. Elements lesser than 0\n6. Concatenation\n7. quit\n");

    char s[100] = "";

    while (scanf("%s", s)) {

        //inc
        if (!strcmp(s, "1")) vd = map_D(&inc, vd);

        //dec
        else if (!strcmp(s, "2")) vd = map_D(&dec, vd);

        //abc
        else if (!strcmp(s, "3")) vd = map_D(&absolute, vd);

        //greater than 0
        else if (!strcmp(s, "4")) {
            vectorD new_vd = where_D(&is_greater0, &vd);
            outputD(&new_vd);
        }

        //lesser than 0
        else if (!strcmp(s, "5")) {
            vectorD new_vd = where_D(&is_lesser0, &vd);
            outputD(&new_vd);
        }

        //concatenation
        else if (!strcmp(s, "6")) {
            int n = 0;
            char sn[100] = "";
            printf("Enter size of vector which you want to concatenate : ");
            scanf("%s", sn);
            while (sn[0] == '-' || is_greater_than_max(sn, MAXN - vd.size)) {
                if (sn[0] == '-') printf("\nERROR : Negative size. TRY AGAIN!\n\n");
                else printf("\nERROR : Too big size, choose less number <= %i. TRY AGAIN\n\n", MAXN - vd.size);
                printf("Enter size of vector which you want to concatenate : ");
                scanf("%s", sn);
            }

            n = convert_str_to_int(sn);

            printf("Enter %i elements separated by a space of your vector : ", n);
            if (n == 0) printf("\n");

            vectorD a = make_vd(n);
            for (int i = 0; i < a.size; ++i) scanf("%lf", &a.p[i]);
            conc_D(&vd, &a);
        } else if (strcmp(s, "7")) printf("\nERROR : Wrong keyword. TRY AGAIN!\n\n");
        else break;

        if (!strcmp(s, "1") || !strcmp(s, "2") || !strcmp(s, "3") || !strcmp(s, "4") ||
            !strcmp(s, "5") || !strcmp(s, "6"))
            outputD(&vd);

        printf("Choose number of option to apply to your elements :\n");
        printf("1. Add 1\n2. Sub 1\n3. Abs\n4. Elements greater than 0\n5. Elements lesser than 0\n6. Concatenation\n7. quit\n");
    }
}