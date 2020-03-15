//
// Created by Vasiliy Evdokimov on 28.02.2020.
//


#include "complex_unit.h"
#include "utils.h"

// *** Constructor ***

complex* MakeComplex(double x, double y){
    complex* c = (complex*)malloc(sizeof(complex));
    c->a = x;
    c->b = y;
    return c;
}

// *** Destructor ***

void DeleteComplex(complex* c){
    if (c) {
        free(c);
        c = NULL;
    }
    else Warning("Trying to free NULL pointer");
}

// *** Getters ***

double GetReal(complex* c) { return c->a; }
double GetImag(complex* c) { return c->b; }

// *** Setters ***

void SetReal(complex* c, double a) { c->a = a; }
void SetImag(complex* c, double b) { c->b = b; }

// *** Operations ***

complex* AddC(complex* a, complex* b){
    return MakeComplex(a->a + b->a, a->b + b->b);
}

complex* SubC(complex* a, complex* b){
    return MakeComplex(a->a - b->a, a->b - b->b);
}

complex* MultC(complex* a, complex* b){
    return MakeComplex(a->a * b->a - a->b * b->b, a->a * b->b + a->b * b->a);
}

complex* DivC(complex* a, complex* b){
    complex* res = MultC(MakeComplex(a->a, a->b), MakeComplex(b->a, -b->b));
    double c = b->a * b->a + b->b * b->b;
    return MakeComplex(res->a / c, res->b / c);
}

// *** Utils ***

complex IncReal(complex c) { return *MakeComplex(GetReal(&c) + 1, GetImag(&c)); }
complex IncImag(complex c) { return *MakeComplex(GetReal(&c), GetImag(&c) + 1); }
complex DecReal(complex c) { return *MakeComplex(GetReal(&c) - 1, GetImag(&c)); }
complex DecImag(complex c) { return *MakeComplex(GetReal(&c), GetImag(&c) - 1); }