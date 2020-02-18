#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct Complex {
    double a;
    double b;
} Complex;

typedef struct Dynamic_Array_Double {
    double* p;
    size_t n;
} vectorD;

typedef struct Dynamic_Array_Complex {
    Complex* p;
    size_t n;
} vectorC;


//vectorD functions :

void outputD(vectorD* vd){
    printf("Your vector : ");
    for (int i = 0; i < vd->n; ++i) printf("%lf ", *(vd->p + i));
    printf("\n");
}

double inc(double x) { return x + 1; }

double dec(double x) { return x - 1; }

double absolute(double x) { return fabs(x); }

vectorD map(double (*f)(double), vectorD vd){
    vectorD new_vd = {NULL, vd.n};
    new_vd.p = (double*)calloc(vd.n, sizeof(double));
    for (int i = 0; i < vd.n; ++i) new_vd.p[i] = f(vd.p[i]);
    return new_vd;
}

void conc(vectorD* x, vectorD* a){
    size_t new_size = x->n + a->n;
    size_t prev_size = x->n;
    x->n = new_size;
    x->p = (double*)realloc(x->p, new_size * sizeof(double));
    for (int i = prev_size, j = 0; i < new_size; ++i, ++j) x->p[i] = a->p[j];
}

int main() {
    int n = 0;
    printf("Write down size of an array : ");
    scanf("%i", &n);
    char s[100] = "";

    bool valid = false;
    while (!valid) {
        printf("Do you want array of real or complex numbers?\nType \"Real\" or \"Complex\" : ");
        scanf("%s", s);

        if (!strcmp(s, "Real")) {
            vectorD vd = {NULL, n};
            vd.p = (double *) calloc(n, sizeof(double));
            printf("Enter %i real numbers : ", n);
            for (int i = 0; i < n; ++i) scanf("%lf", vd.p + i);

            //Vector Output
            outputD(&vd);


            printf("\nWhat do you want to do with your vector?\n");
            printf("Choose function to apply to your elements :\n");
            printf("1. inc\n2. dec\n3. abs\n4. concatenation\n5. quit\n");

            while(scanf("%s", s)) {

                if (!strcmp(s, "inc")) {
                    vd = map(&inc, vd);
                    outputD(&vd);
                } else if (!strcmp(s, "dec")) {
                    vd = map(&dec, vd);
                    outputD(&vd);
                } else if (!strcmp(s, "abs")) {
                    vd = map(&absolute, vd);
                    outputD(&vd);
                }
                else if (!strcmp(s, "concatenation")){
                    int n = 0;
                    printf("Enter size of vector which you want to concatenate : ");
                    scanf("%i", &n);
                    printf("Enter %i elements separated by a space of your vector : ", n);

                    vectorD a = {NULL, n};
                    a.p = (double*)calloc(n, sizeof(double));
                    conc(&vd, &a);
                    outputD(&vd);
                }
                else if (strcmp(s, "quit")) printf("\nERROR : Wrong keyword. TRY AGAIN!\n\n");
                else break;
                printf("Choose function to apply to your elements :\n");
                printf("1. inc\n2. dec\n3. abs\n4. concatenation\n5. quit\n");
            }

            valid = true;
        } else if (!strcmp(s, "Complex")) {
            valid = true;
        } else printf("\nERROR : Invalid keyword. TRY AGAIN.\n\n");
        //printf("%s", s);
    }

    return 0;
}
