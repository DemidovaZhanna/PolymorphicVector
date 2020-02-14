#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int n = 0;

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
    for (int i = 0; i < n; ++i) printf("%lf ", *(vd->p + i));
}


int main() {
    printf("Write down size of an array : ");
    scanf("%i", &n);
    char s[100] = "";

    bool valid = false;
    while (!valid) {
        printf("Do you want array of real or complex numbers?\nType \"Real\" or \"Complex\" : ");
        scanf("%s", s);

        if (!strcmp(s, "Real")) {
            vectorD darr = {NULL, n};
            darr.p = (double *) calloc(n, sizeof(double));
            printf("Enter %i real numbers : ", n);
            for (int i = 0; i < n; ++i) scanf("%lf", darr.p + i);

            //Vector Output
            printf("Your vector : ");
            outputD(&darr);

            printf("\nWhat do you want to do with your vector?\n");

            

            valid = true;
        } else if (!strcmp(s, "Complex")) {
            valid = true;
        } else printf("\nERROR : Invalid keyword. TRY AGAIN.\n\n");
        //printf("%s", s);
    }

    return 0;
}
