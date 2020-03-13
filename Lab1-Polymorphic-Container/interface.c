//
// Created by Vasiliy Evdokimov on 12.03.2020.
//

#include "interface.h"


const size_t MAXN;

void interface(size_t size, int type){
    Eltype T = -1;
    if (type == 1) T = INT;
    else if (type == 2) T = COMPLEX;
    else { UnknownType(); return; }

    Vector* v = MakeVector(size, T);


    if (GetElType(v) == INT) {
        printf("Enter %zu integer numbers : ", GetSize(v));
        size_t n = GetSize(v);
        for (size_t i = 0; i < n; ++i) scanf("%d", GetDataI(v) + i);

        OutputVector(v);

        printf("\nWhat do you want to do with your vector?\n");
        printf("Choose number of option to apply to your elements :\n");
        printf("1. Inc\n2. Dec\n3. Abs\n4. Elements greater than 0\n5. Elements lesser than 0\n6. Concatenation\n7. Quit\n");

        char s[100] = "";

        while (scanf("%s", s)){

            //Inc
            if (!strcmp(s, "1")) v = MapI(&IncI, v);

            //Dec
            else if (!strcmp(s, "2")) v = MapI(&DecI, v);

            //Abs
            else if (!strcmp(s, "3")) v = MapI(&AbsoluteI, v);

            //Elements greater than 0
            else if (!strcmp(s, "4")){
                Vector* new_v = FilterI(&IsGreaterThan0, v);
                OutputVector(new_v);
            }

            //Elements lesser than 0
            else if (!strcmp(s, "5")){
                Vector* new_v = FilterI(&IsLesserThan0, v);
                OutputVector(new_v);
            }

            //Concatenation
            else if (!strcmp(s, "6")){
                char sn[100] = "";
                printf("Enter size of vector which you want to concatenate to your vector : ");
                scanf("%s", sn);
                while (sn[0] == '-' || is_greater_than_max(sn, MAXN - GetSize(v)) || !is_num(sn)) {
                    if (sn[0] == '-') printf("\nERROR : Negative size. TRY AGAIN!\n\n");
                    else if (!is_num(sn)) printf("\nERROR : It's not a number. TRY AGAIN\n\n");
                    else printf("\nERROR : Too big size, choose less number <= %zu. TRY AGAIN\n\n", MAXN - GetSize(v));
                    printf("Enter size of vector which you want to concatenate : ");
                    scanf("%s", sn);
                }

                size_t n = convert_str_to_int(sn);

                printf("Enter %zu elements separated by space of your vector : ", n);
                if (n == 0) printf("\n");

                Vector* v2 = MakeVector(n, INT);
                for (size_t i = 0; i < GetSize(v2); ++i) scanf("%d", &GetDataI(v2)[i]);
                Concatenation(v, v2);

                DeleteVector(v2);
            }

            else if (strcmp(s, "7")) printf("\nERROR : Wrong keyword. TRY AGAIN!\n\n");

            //Quit
            else break;

            if (!strcmp(s, "1") || !strcmp(s, "2") || !strcmp(s, "3") || !strcmp(s, "4") ||
                !strcmp(s, "5") || !strcmp(s, "6")) OutputVector(v);

            printf("Choose number of option to apply to your elements :\n");
            printf("1. Inc\n2. Dec\n3. Abs\n4. Elements greater than 0\n5. Elements lesser than 0\n6. Concatenation\n7. Quit\n");
        }
    }
    else if (GetElType(v) == COMPLEX){
        printf("Enter %zu complex numbers \"<real> <imag>\" : ", GetSize(v));
        size_t n = GetSize(v);
        for (size_t i = 0; i < n; ++i) scanf("%lf %lfi", &GetDataC(v)[i].a, &GetDataC(v)[i].b);

        OutputVector(v);

        printf("\nWhat do you want to do with your vector?\n");
        printf("Choose number of option to apply to your elements :\n");
        printf("1. Inc real \n2. Inc imag \n3. Dec real \n4. Dec imag \n5. Concatenation \n6. Quit\n");

        char s[100] = "";

        while (scanf("%s", s)){

            //Inc real
            if (!strcmp(s, "1")) v = MapC(&IncReal, v);

            //Inc imag
            else if (!strcmp(s, "2")) v = MapC(&IncImag, v);

            //Dec real
            else if (!strcmp(s, "3")) v = MapC(&DecReal, v);

            //Dec imag
            else if (!strcmp(s, "4")) v = MapC(&DecImag, v);

            //Concatenation
            else if (!strcmp(s, "5")){
                char sn[100] = "";
                printf("Enter size of vector which you want to concatenate : ");
                scanf("%s", sn);
                while (sn[0] == '-' || is_greater_than_max(sn, MAXN - GetSize(v)) || !is_num(sn)) {
                    if (sn[0] == '-') printf("\nERROR : Negative size. TRY AGAIN!\n\n");
                    else if (!is_num(sn)) printf("\nERROR : It's not a number. TRY AGAIN\n\n");
                    else printf("\nERROR : Too big size, choose less number <= %zu. TRY AGAIN\n\n", MAXN - GetSize(v));
                    printf("Enter size of vector which you want to concatenate : ");
                    scanf("%s", sn);
                }

                size_t n = convert_str_to_int(sn);

                printf("Enter %zu elements \"<real> <imag>\" : ", n);
                if (n == 0) printf("\n");

                Vector* v2 = MakeVector(n, COMPLEX);
                for (size_t i = 0; i < GetSize(v2); ++i) scanf("%lf %lf", &GetDataC(v)[i].a, &GetDataC(v)[i].b);
                Concatenation(v, v2);

                DeleteVector(v2);
            }
            else if (strcmp(s, "6")) printf("\nERROR : Wrong keyword. TRY AGAIN!\n\n");
            else break;

            if (!strcmp(s, "1") || !strcmp(s, "2") || !strcmp(s, "3") || !strcmp(s, "4") ||
                !strcmp(s, "5")) OutputVector(v);


            printf("Choose number of option to apply to your elements :\n");
            printf("1. Inc real \n2. Inc imag \n3. Dec real \n4. Dec imag \n5. Concatenation \n6. Quit\n");
        }
    }
    else { UnknownType(); return; }

    DeleteVector(v);
}