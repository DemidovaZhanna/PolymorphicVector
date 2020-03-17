//
// Created by Vasiliy Evdokimov on 28.02.2020.
//

#ifndef LABA1_COMPLEX_UNIT_H
#define LABA1_COMPLEX_UNIT_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Complex {
    double real;
    double imag;
} complex;

// *** Constructor ***

complex* MakeComplex(double, double);

// *** Destructor ***

void DeleteComplex(complex*);

// *** Input and Output

void OutputComplex(complex*);

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

// *** Predicates ***

bool IsPositiveReal (complex);
bool IsPositiveImag (complex);
bool IsPositiveRealAndImag (complex);

// *** Utils ***

complex IncReal(complex);
complex IncImag(complex);
complex DecReal(complex);
complex DecImag(complex);


#endif //LABA1_COMPLEX_UNIT_H
