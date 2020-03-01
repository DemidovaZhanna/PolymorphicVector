//
// Created by Vasiliy Evdokimov on 28.02.2020.
//

#ifndef LABA1_COMPLEXV_H
#define LABA1_COMPLEXV_H

typedef struct Complex {
    double a;
    double b;
} complex;

complex make_complex(double, double);

complex add(complex, complex);
complex sub(complex, complex);
complex mult(complex, complex);
complex div_c(complex, double);
complex divide(complex, complex);

#endif //LABA1_COMPLEXV_H
