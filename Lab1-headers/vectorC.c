//
// Created by Vasiliy Evdokimov on 28.02.2020.
//

#include "vectorC.h"
#include "general_fun.h"

void expand_capacity_C(vectorC* vd){
    vd->capacity *= 2;
    vd->p = (complex*)realloc(vd->p, vd->capacity * sizeof(complex));
}

vectorC make_vc(size_t size){
    vectorC vd = {NULL, size, max(size, 100)};
    vd.p = (complex*)calloc(vd.capacity, sizeof(complex));
    return vd;
}

void add_element_C(vectorC* vd, complex c){
    if (vd->capacity < vd->size + 1) expand_capacity_C(vd);
    ++vd->size;
    vd->p[vd->size - 1] = c;
}

void outputC(vectorC* vd){
    printf("Your vector : ");
    int n = vd->size;
    for (int i = 0; i < n; ++i) printf("%lf + %lfi, ", vd->p[i].a, vd->p[i].b);
    printf("\n");
}

complex inc_real(complex c) { return make_complex(c.a + 1, c.b); }
complex inc_imag(complex c) { return make_complex(c.a, c.b + 1); }

complex dec_real(complex c) { return make_complex(c.a - 1, c.b); }
complex dec_imag(complex c) { return make_complex(c.a, c.b - 1); }

//double absolute(complex c) { return sqrt(square(c.a) + square(c.b)); }

vectorC map_C(complex (*f)(complex), vectorC vc){
    vectorC new_vc = {NULL, vc.size};
    new_vc.p = (complex*)calloc(vc.size, sizeof(complex));
    int n = vc.size;
    for (int i = 0; i < n; ++i) new_vc.p[i] = f(vc.p[i]);
    return new_vc;
}


vectorC where_C(bool (*filter)(complex), vectorC* vd) {
    int n = vd->size;
    vectorC new_vd = make_vc(0);
    for (int i = 0; i < n; ++i) if (filter(vd->p[i])) add_element_C(&new_vd, vd->p[i]);
    return new_vd;
}

void conc_C(vectorC* x, vectorC* a){
    size_t new_size = x->size + a->size;
    size_t prev_size = x->size;
    x->size = new_size;
    x->p = (complex*)realloc(x->p, new_size * sizeof(complex));
    for (int i = prev_size, j = 0; i < new_size; ++i, ++j) x->p[i] = a->p[j];
}

