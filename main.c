#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const int MAXN = (1 << 31) - 1;

typedef struct Complex {
    double a;
    double b;
} Complex;

typedef struct Dynamic_Array_Double {
    double* p;
    size_t size;
    size_t capacity;
} vectorD;

typedef struct Dynamic_Array_Complex {
    Complex* p;
    size_t size;
    size_t capacity;
} vectorC;

//General functions

double max(double a, double b){
    return (a <= b ? b : a);
}

bool is_greater_than_max(char const * s, const int max) {
    int n = strlen(s);
    if (n > 10) return true;
    else if (n < 10) return false;
    else {
        int p10 = 1000000000;
        for (int i = 0; i < n; ++i){
            if ((s[i] - '0') > (max / p10) % 10) return true;
            p10 /= 10;
        }
    }
    return false;
}

int convert_str_to_int(char const * s){
    int res = 0;
    int n = strlen(s);
    int p10 = 1;
    for (int i = 0; i < n - 1; ++i) p10 *= 10;

    for (int i = 0; i < n; ++i) res += (s[i] - '0') * p10, p10 /= 10;

    return res;
}

//vectorD functions :

void expand_capacity(vectorD* vd){
    vd->capacity *= 2;
    vd->p = (double*)realloc(vd->p, vd->capacity * sizeof(double));
}

vectorD make_vd(size_t size){
    vectorD vd = {NULL, size, max(size, 100)};
    vd.p = (double*)calloc(vd.capacity, sizeof(double));
    return vd;
}

void add_element(vectorD* vd, double a){
    if (vd->capacity < vd->size + 1) expand_capacity(vd);
    ++vd->size;
    vd->p[vd->size - 1] = a;
}

void outputD(vectorD* vd){
    printf("Your vector : ");
    int n = vd->size;
    for (int i = 0; i < n; ++i) printf("%lf ", *(vd->p + i));
    printf("\n");
}

double inc(double x) { return x + 1; }

double dec(double x) { return x - 1; }

double absolute(double x) { return fabs(x); }

vectorD map(double (*f)(double), vectorD vd){
    vectorD new_vd = {NULL, vd.size};
    new_vd.p = (double*)calloc(vd.size, sizeof(double));
    int n = vd.size;
    for (int i = 0; i < n; ++i) new_vd.p[i] = f(vd.p[i]);
    return new_vd;
}

bool is_greater0(double a) { return a > 0; }
bool is_lesser0(double a) { return a < 0; }

vectorD where(bool (*filter)(double), vectorD* vd) {
    int n = vd->size;
    vectorD new_vd = make_vd(0);
    for (int i = 0; i < n; ++i) if (filter(vd->p[i])) add_element(&new_vd, vd->p[i]);
    return new_vd;
}


void conc(vectorD* x, vectorD* a){
    size_t new_size = x->size + a->size;
    size_t prev_size = x->size;
    x->size = new_size;
    x->p = (double*)realloc(x->p, new_size * sizeof(double));
    for (int i = prev_size, j = 0; i < new_size; ++i, ++j) x->p[i] = a->p[j];
}


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

        if (!strcmp(s, "Real")) {
            vectorD vd = make_vd(n);
            printf("Enter %i real numbers : ", n);
            n = vd.size;
            for (int i = 0; i < n; ++i) scanf("%lf", vd.p + i);

            outputD(&vd);

            printf("\nWhat do you want to do with your vector?\n");
            printf("Choose number of option to apply to your elements :\n");
            printf("1. Add 1\n2. Sub 1\n3. Abs\n4. Elements greater than 0\n5. Elements lesser than 0\n6. Concatenation\n7. quit\n");

            while(scanf("%s", s)) {

                //inc
                if (!strcmp(s, "1")) vd = map(&inc, vd);

                //dec
                else if (!strcmp(s, "2")) vd = map(&dec, vd);

                //abc
                else if (!strcmp(s, "3")) vd = map(&absolute, vd);

                //greater than 0
                else if (!strcmp(s, "4")){
                    vectorD new_vd = where(&is_greater0, &vd);
                    outputD(&new_vd);
                }

                //lesser than 0
                else if (!strcmp(s, "5")){
                    vectorD new_vd = where(&is_lesser0, &vd);
                    outputD(&new_vd);
                }

                //concatenation
                else if (!strcmp(s, "6")){
                    int n = 0;
                    printf("Enter size of vector which you want to concatenate : ");
                    scanf("%s", sn);
                    while (sn[0] == '-' || is_greater_than_max(sn, MAXN - vd.size)){
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
                    conc(&vd, &a);
                }
                else if (strcmp(s, "7")) printf("\nERROR : Wrong keyword. TRY AGAIN!\n\n");
                else break;

                if (!strcmp(s, "1") || !strcmp(s, "2") || !strcmp(s, "3") || !strcmp(s, "4") ||
                    !strcmp(s, "5") || !strcmp(s, "6") || !strcmp(s, "7")) outputD(&vd);

                printf("Choose number of option to apply to your elements :\n");
                printf("1. Add 1\n2. Sub 1\n3. Abs\n4. Elements greater than 0\n5. Elements lesser than 0\n6. Concatenation\n7. quit\n");
            }

        }
        else if (!strcmp(s, "Complex")) {}
        else printf("\nERROR : Invalid keyword. TRY AGAIN.\n\n");

        if (!strcmp(s, "quit") || !strcmp(s, "7")) break;
        printf("Do you want array of real or complex numbers?\nType \"Real\" or \"Complex\" : ");
    }

    return 0;
}
