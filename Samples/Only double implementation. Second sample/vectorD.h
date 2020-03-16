//
// Created by Vasiliy Evdokimov on 27.02.2020.
//

#ifndef LABA1_VECTORD_H
#define LABA1_VECTORD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct Dynamic_Array_Double {
    double* p;
    size_t size;
    size_t capacity;
} vectorD;

void expand_capacity(vectorD*);
vectorD make_vd(size_t);
void add_element(vectorD*, double);
void outputD(vectorD*);

double inc(double);
double dec(double);
double absolute(double);
bool is_greater0(double);
bool is_lesser0(double);

vectorD map(double (*)(double), vectorD);
vectorD where(bool (*)(double), vectorD*);
void conc(vectorD*, vectorD*);


#endif //LABA1_VECTORD_H
