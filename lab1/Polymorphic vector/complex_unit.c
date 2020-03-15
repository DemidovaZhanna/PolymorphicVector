//
// Created by Vasiliy Evdokimov on 28.02.2020.
//


#include "complex_unit.h"
#include "utils.h"

// *** Constructor ***

complex* MakeComplex(double x, double y){
    complex* c = (complex*)malloc(sizeof(complex));
    c->real = x;
    c->imag = y;
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

double GetReal(complex* c) { return c->real; }
double GetImag(complex* c) { return c->imag; }

// *** Setters ***

void SetReal(complex* c, double a) { c->real = a; }
void SetImag(complex* c, double b) { c->imag = b; }

// *** Operations ***

complex* AddC(complex* a, complex* b){
    return MakeComplex(GetReal(a) + GetReal(b), GetImag(a) + GetImag(b));
}

complex* SubC(complex* a, complex* b){
    return MakeComplex(GetReal(a) - GetReal(b), GetImag(a) - GetImag(b));
}

complex* MultC(complex* a, complex* b){
    return MakeComplex(GetReal(a) * GetReal(b) - GetImag(a) * GetImag(b), GetReal(a) * GetImag(b) + GetImag(a) * GetReal(b));
}

complex* DivC(complex* a, complex* b){
    complex* res = MultC(MakeComplex(GetReal(a), GetImag(a)), MakeComplex(GetReal(b), -GetImag(b)));
    double c = GetReal(b) * GetReal(b) + GetImag(b) * GetImag(b);
    return MakeComplex(GetReal(res) / c, GetImag(res) / c);
}

// *** Utils ***

complex IncReal(complex c) { return *MakeComplex(GetReal(&c) + 1, GetImag(&c)); }
complex IncImag(complex c) { return *MakeComplex(GetReal(&c), GetImag(&c) + 1); }
complex DecReal(complex c) { return *MakeComplex(GetReal(&c) - 1, GetImag(&c)); }
complex DecImag(complex c) { return *MakeComplex(GetReal(&c), GetImag(&c) - 1); }