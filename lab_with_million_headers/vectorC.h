//
// Created by Vasiliy Evdokimov on 28.02.2020.
//

#ifndef LABA1_VECTORC_H
#define LABA1_VECTORC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "complexV.h"

typedef struct Dynamic_Array_Complex {
    complex* p;
    size_t size;
    size_t capacity;
} vectorC;


void expand_capacity_C(vectorC*);
vectorC make_vc(size_t);
void add_element_C(vectorC*, complex);
void outputC(vectorC*);

complex inc_real(complex);
complex inc_imag(complex);
complex dec_real(complex);
complex dec_imag(complex);
double absolute_C(complex);

vectorC map_C(complex (*)(complex), vectorC);
vectorC where_C(bool (*)(complex), vectorC*);
void conc_C(vectorC*, vectorC*);

#endif //LABA1_VECTORC_H
