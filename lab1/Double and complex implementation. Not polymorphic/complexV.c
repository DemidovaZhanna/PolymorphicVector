//
// Created by Vasiliy Evdokimov on 28.02.2020.
//

#include "complexV.h"

complex make_complex(double x, double y){
    complex com = {x, y};
    return com;
}

complex add_c(complex a, double c){
    complex res = add(a, make_complex(c, 0));
    return make_complex(res.a, res.b);
}

complex add(complex a, complex b){
    return make_complex(a.a + b.a, a.b + b.b);
}

complex sub_c(complex a, double c){
    complex res = sub(a, make_complex(c, 0));
    return make_complex(res.a, res.b);
}

complex sub(complex a, complex b){
    return make_complex(a.a - b.a, a.b - b.b);
}

complex mult_c(complex a, double c){
    return make_complex(a.a * c, a.b * c);
}

complex mult(complex a, complex b){
    return make_complex(a.a * b.a - a.b * b.b, a.a * b.b + a.b * b.a);
}

complex div_c(complex a, double c){
    return make_complex(a.a / c, a.b/ c);
}

complex divide(complex a, complex b){
    complex res = mult(make_complex(a.a, a.b), make_complex(b.a, -b.b));
    int c = b.a * b.a + b.b * b.b;
    return div_c(res, c);
}