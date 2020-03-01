//
// Created by Vasiliy Evdokimov on 28.02.2020.
//

#include "interface_vectorC.h"

#include <stdio.h>
#include "vectorC.h"
#include "general_fun.h"
#include <stdlib.h>

const int MAXN = (1U << 31) - 1;

void interface_vectorC(int n) {
    vectorC vc = make_vc(n);
    printf("Enter %i real numbers <real> <imag> : ", n);
    n = vc.size;
    for (int i = 0; i < n; ++i) scanf("%lf %lfi", &vc.p[i].a, &vc.p[i].b);

    outputC(&vc);

    printf("\nWhat do you want to do with your vector?\n");
    printf("Choose number of option to apply to your elements :\n");
    printf("1. Inc real \n2. Inc imag \n3. Dec real \n4. Dec imag \n5. Concatenation \n6. quit\n");


    char s[100] = "";

    while (scanf("%s", s)) {

        //Inc real
        if (!strcmp(s, "1")) vc = map_C(&inc_real, vc);

        //Inc imag
        else if (!strcmp(s, "2")) vc = map_C(&inc_imag, vc);

        //Dec real
        else if (!strcmp(s, "3")) vc = map_C(&dec_real, vc);

        //Dec imag
        else if (!strcmp(s, "4")) vc = map_C(&dec_imag, vc);

        //Concatenation
        else if (!strcmp(s, "5")) {
            int n = 0;
            char sn[100] = "";
            printf("Enter size of vector which you want to concatenate : ");
            scanf("%s", sn);
            while (sn[0] == '-' || is_greater_than_max(sn, MAXN - vc.size)) {
                if (sn[0] == '-') printf("\nERROR : Negative size. TRY AGAIN!\n\n");
                else printf("\nERROR : Too big size, choose less number <= %i. TRY AGAIN\n\n", MAXN - vc.size);
                printf("Enter size of vector which you want to concatenate : ");
                scanf("%s", sn);
            }

            n = convert_str_to_int(sn);

            printf("Enter %i elements <real> <imag> : ", n);
            if (n == 0) printf("\n");

            vectorC a = make_vc(n);
            for (int i = 0; i < a.size; ++i) scanf("%lf %lf", &a.p[i].a, &a.p[i].b);
            conc_C(&vc, &a);
        }
        else if (strcmp(s, "6")) printf("\nERROR : Wrong keyword. TRY AGAIN!\n\n");
        else break;

        if (!strcmp(s, "1") || !strcmp(s, "2") || !strcmp(s, "3") || !strcmp(s, "4") ||
            !strcmp(s, "5"))
            outputC(&vc);

        printf("Choose number of option to apply to your elements :\n");
        printf("1. Inc real \n2. Inc imag \n3. Dec real \n4. Dec imag \n5. Concatenation \n6. quit\n");
    }
}
