//
// Created by Vasiliy Evdokimov on 12.03.2020.
//

#include "interface_vector.h"

const size_t MAXN;

void interface_vector(){

    printf("Write down size of vector : ");

    size_t size = read_correct_num(0);
    char s[100] = "";

    printf("Choose type of your vector :\n"
           "1. Integer\n"
           "2. Complex\n");

    Eltype T = -1;
    while (scanf("%s", s)) {
        if (!strcmp(s, "Integer") || !strcmp(s, "1")) { T = INT; break; }
        else if (!strcmp(s, "Complex") || !strcmp(s, "2")) { T = COMPLEX; break; }
        else Warning("Invalid keyword.");
        printf("Choose type of your vector :\n"
               "1. Integer\n"
               "2. Complex\n");
    }

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
               "4. Square\n"
               "5. Elements greater than 0\n"
               "6. Elements lesser than 0\n"
               "7. Concatenation\n"
               "8. Even numbers\n"
               "9. Odd numbers\n"
               "10. Quit\n");

        char s[100] = "";

        while (scanf("%s", s)){

            //Inc
            if (!strcmp(s, "1")) v = MapI(&IncI, v);

            //Dec
            else if (!strcmp(s, "2")) v = MapI(&DecI, v);

            //Abs
            else if (!strcmp(s, "3")) v = MapI(&AbsoluteI, v);

            //Square
            else if (!strcmp(s, "4")) v = MapI(&Square, v);

            //Elements greater than 0
            else if (!strcmp(s, "5")){
                Vector* new_v = FilterI(&IsGreaterThan0, v);
                OutputVector(new_v);
            }

            //Elements lesser than 0
            else if (!strcmp(s, "6")){
                Vector* new_v = FilterI(&IsLesserThan0, v);
                OutputVector(new_v);
            }

            //Concatenation
            else if (!strcmp(s, "7")){
                printf("Enter size of vector which you want to concatenate to your vector : ");

                size_t n = read_correct_num(GetSize(v));

                Vector* v2 = MakeVector(n, INT);
                bool is_data_correct = InputVector(v2);
                while (!is_data_correct) is_data_correct = InputVector(v2);

                Concatenation(v, v2);

                DeleteVector(v2);
            }

            //Even numbers
            else if (!strcmp(s, "8")){
                Vector* new_v = FilterI(&IsEven, v);
                OutputVector(new_v);
            }

            //Odd numbers
            else if (!strcmp(s, "9")){
                Vector* new_v = FilterI(&IsOdd, v);
                OutputVector(new_v);
            }

            //Some bullshit
            else if (strcmp(s, "10")) Warning("Wrong keyword");

            //Quit
            else break;

            if (!strcmp(s, "1") || !strcmp(s, "2") || !strcmp(s, "3") || !strcmp(s, "4") ||
                !strcmp(s, "5") || !strcmp(s, "6") || !strcmp(s, "7") || !strcmp(s, "8") ||
                !strcmp(s, "9")) OutputVector(v);

            printf("\nWhat do you want to do with your vector?\n"
                   "Choose number of option to apply to your elements :\n"
                   "1. Inc\n"
                   "2. Dec\n"
                   "3. Abs\n"
                   "4. Square\n"
                   "5. Elements greater than 0\n"
                   "6. Elements lesser than 0\n"
                   "7. Concatenation\n"
                   "8. Even numbers\n"
                   "9. Odd numbers\n"
                   "10. Quit\n");
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