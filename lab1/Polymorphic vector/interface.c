//
// Created by Vasiliy Evdokimov on 12.03.2020.
//

#include "interface.h"

const size_t MAXN;

void interface(size_t size, Eltype type){
    Eltype T = -1;
    if (type == INT) T = INT;
    else if (type == COMPLEX) T = COMPLEX;
    else UnknownType();

    Vector* v = MakeVector(size, T);
    bool is_data_correct = InputVector(v);
    while (!is_data_correct) is_data_correct = InputVector(v);
    OutputVector(v);

    if (GetElType(v) == INT) {

        printf("\nWhat do you want to do with your vector?\n"
               "Choose number of option to apply to your elements :\n"
               "1. Inc\n"
               "2. Dec\n"
               "3. Abs\n"
               "4. Elements greater than 0\n"
               "5. Elements lesser than 0\n"
               "6. Concatenation\n"
               "7. Even numbers\n"
               "8. Odd numbers\n"
               "9. Quit\n");

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
                printf("Enter size of vector which you want to concatenate to your vector : ");

                size_t n = read_correct_num(GetSize(v));

                Vector* v2 = MakeVector(n, INT);
                bool is_data_correct = InputVector(v2);
                while (!is_data_correct) is_data_correct = InputVector(v2);

                Concatenation(v, v2);

                DeleteVector(v2);
            }

            //Even numbers
            else if (!strcmp(s, "7")){
                Vector* new_v = FilterI(&IsEven, v);
                OutputVector(new_v);
            }

            //Odd numbers
            else if (!strcmp(s, "8")){
                Vector* new_v = FilterI(&IsOdd, v);
                OutputVector(new_v);
            }

            //Some bullshit
            else if (strcmp(s, "9")) Warning("Wrong keyword");

            //Quit
            else break;

            if (!strcmp(s, "1") || !strcmp(s, "2") || !strcmp(s, "3") || !strcmp(s, "4") ||
                !strcmp(s, "5") || !strcmp(s, "6") || !strcmp(s, "7") || !strcmp(s, "8")) OutputVector(v);

            printf("\nWhat do you want to do with your vector?\n"
                   "Choose number of option to apply to your elements :\n"
                   "1. Inc\n"
                   "2. Dec\n"
                   "3. Abs\n"
                   "4. Elements greater than 0\n"
                   "5. Elements lesser than 0\n"
                   "6. Concatenation\n"
                   "7. Even numbers\n"
                   "8. Odd numbers\n"
                   "9. Quit\n");
        }
    }
    else if (GetElType(v) == COMPLEX){

        printf("\nWhat do you want to do with your vector?\n"
               "Choose number of option to apply to your elements :\n"
               "1. Inc real \n"
               "2. Inc imag \n"
               "3. Dec real \n"
               "4. Dec imag \n"
               "5. Concatenation \n"
               "6. Quit\n");

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
                printf("Enter size of vector which you want to concatenate : ");

                size_t n = read_correct_num(GetSize(v));

                Vector* v2 = MakeVector(n, COMPLEX);
                bool is_data_correct = InputVector(v2);
                while (!is_data_correct) is_data_correct = InputVector(v2);

                Concatenation(v, v2);

                DeleteVector(v2);
            }

            //Some bullshit
            else if (strcmp(s, "6")) Warning("Wrong keyword");

            //Quit
            else break;

            if (!strcmp(s, "1") || !strcmp(s, "2") || !strcmp(s, "3") || !strcmp(s, "4") ||
                !strcmp(s, "5")) OutputVector(v);


            printf("Choose number of option to apply to your elements :\n"
                   "1. Inc real \n"
                   "2. Inc imag \n"
                   "3. Dec real \n"
                   "4. Dec imag \n"
                   "5. Concatenation \n"
                   "6. Quit\n");
        }
    }
    else UnknownType();

    DeleteVector(v);
}