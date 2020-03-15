//
// Created by Vasiliy Evdokimov on 28.02.2020.
//

#ifndef LABA1_COMPLEX_UNIT_H
#define LABA1_COMPLEX_UNIT_H

#include <stdlib.h>

typedef struct Complex {
    double a;
    double b;
} complex;

// *** Constructor ***

complex* MakeComplex(double, double);

// *** Destructor ***

void DeleteComplex(complex*);

// *** Getters ***

double GetReal(complex*);
double GetImag(complex*);

// *** Setters ***

void SetReal(complex*, double);
void SetImag(complex*, double);

// *** Operations ***

complex* AddC(complex*, complex*);
complex* SubC(complex*, complex*);
complex* Multc(complex*, complex*);
complex* DivC(complex*, complex*);


#endif //LABA1_COMPLEX_UNIT_H
