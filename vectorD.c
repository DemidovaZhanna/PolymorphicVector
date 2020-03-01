//
// Created by Vasiliy Evdokimov on 27.02.2020.
//

#include "vectorD.h"
#include "general_fun.h"

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

vectorD map_D(double (*f)(double), vectorD vd){
    vectorD new_vd = {NULL, vd.size};
    new_vd.p = (double*)calloc(vd.size, sizeof(double));
    int n = vd.size;
    for (int i = 0; i < n; ++i) new_vd.p[i] = f(vd.p[i]);
    return new_vd;
}

bool is_greater0(double a) { return a > 0; }
bool is_lesser0(double a) { return a < 0; }

vectorD where_D(bool (*filter)(double), vectorD* vd) {
    int n = vd->size;
    vectorD new_vd = make_vd(0);
    for (int i = 0; i < n; ++i) if (filter(vd->p[i])) add_element(&new_vd, vd->p[i]);
    return new_vd;
}

void conc_D(vectorD* x, vectorD* a){
    size_t new_size = x->size + a->size;
    size_t prev_size = x->size;
    x->size = new_size;
    x->p = (double*)realloc(x->p, new_size * sizeof(double));
    for (int i = prev_size, j = 0; i < new_size; ++i, ++j) x->p[i] = a->p[j];
}

