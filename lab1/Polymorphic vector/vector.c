
//
// Created by Vasiliy Evdokimov on 04.03.2020.
//

#include "vector.h"

// *** Console error information ***

void UnknownType(){
    printf("\n\nERROR : Unknown type. Undefined behaviour.\n\n");
    exit(EXIT_FAILURE);
}

// *** Constructor ***

Vector* MakeVector(size_t size, Eltype eltype) {
    Vector* v = (Vector*)malloc(sizeof(Vector));

    v->eltype = eltype;
    v->size = size;
    v->capacity = max(size, 100);

    size_t type_size = 0;
    if (v->eltype == INT) type_size = sizeof(int);
    else if (v->eltype == COMPLEX) type_size = sizeof(complex);
    else UnknownType();

    v->data = calloc(v->size, type_size);

    return v;
};

// *** Destructor ***

void DeleteVector(Vector* v) {
    if (v){
        FreeData(v->data);
        FreeData(v);
        v = NULL;
    }
}

void FreeData(void* ptr) {
    if (ptr) { free(ptr); ptr = NULL; }
}

// *** Getters ***

size_t GetSize(Vector const * v){
    return v->size;
}

size_t GetCapacity(Vector const * v){
    return v->capacity;
}

void* GetData(Vector const * v){
    return v->data;
}

int* GetDataI(Vector const * v){
    return (int*)v->data;
}

complex* GetDataC(Vector const * v){
    return (complex*)v->data;
}

Eltype GetElType(Vector const * v){
    return v->eltype;
}

// *** Setters ***

void SetSize(Vector* v, size_t size) { v->size = size; }

void SetCapacity(Vector* v, size_t capacity) { v->capacity = capacity; }

void SetElement(Vector* v, size_t i, void* d) {
    Eltype T = v->eltype;
    if (T == INT) GetDataI(v)[i] = *(int*)d;
    else if (T == COMPLEX) GetDataC(v)[i] = *(complex*)d;
    else UnknownType();
}

void SetData(Vector* v, void* ptr) {
    FreeData(GetData(v));
    v->data = ptr;
}

//Function to set data with pointer being allocated via realloc
//I can't use SetData for that purpose because pointer which
//was given to realloc as an argument can be freed already
//so in SetData I will free him again which cause
//undefined behaviour
//Even if realloc expand the given area there wouldn't be
//any memory leaks because that is the same pointer which
//points to a larger are at the same start
//Check documentation (cppreference) for more info
void SetDataRC(Vector* v, void* ptr_realloc){
    v->data = ptr_realloc;
}

// *** Functions that change vector ***

void ExpandCapacity(Vector* v) {
    Eltype T = GetElType(v);
    if (T == INT) {
        SetCapacity(v, GetCapacity(v) * 2);
        SetDataRC(v, realloc(GetDataI(v), GetCapacity(v) * sizeof(int)));
    }
    else if (T == COMPLEX) {
        SetCapacity(v, GetCapacity(v) * 2);
        SetDataRC(v, realloc(GetDataC(v), GetCapacity(v) * sizeof(complex)));
    }
    else UnknownType();
}

void PushBack(Vector* v, void* d){
    Eltype T = GetElType(v);
    if (T == INT) PushBackI(v, d);
    else if (T == COMPLEX) PushBackC(v, d);
    else UnknownType();
}

void PushBackI(Vector* v, int* d){
    if (GetCapacity(v) < GetSize(v) + 1) ExpandCapacity(v);
    SetSize(v, GetSize(v) + 1);
    SetElement(v, GetSize(v) - 1, d);
}

void PushBackC(Vector* v, complex* c){
    if (GetCapacity(v) < GetSize(v) + 1) ExpandCapacity(v);
    SetSize(v, GetSize(v) + 1);
    SetElement(v, GetSize(v) - 1, c);
}

// *** Output ***

void OutputVector(Vector* v){
    printf("Your vector : ");
    size_t size = GetSize(v);
    Eltype T = GetElType(v);
    if (size == 0) { printf("\n"); return; }

    if (T == INT) { for (size_t i = 0; i < size - 1; ++i) printf("%d, ", GetDataI(v)[i]); printf("%d\n", GetDataI(v)[size - 1]); }
    else if (T == COMPLEX) { for (size_t i = 0; i < size - 1; ++i) printf("%lf + %lfi, ", GetDataC(v)[i].a, GetDataC(v)[i].b); printf("%lf + %lfi\n", GetDataC(v)[size - 1].a, GetDataC(v)[size - 1].b); }
    else UnknownType();
}

// *** General Functions ***

Vector* MapI(int (*f)(int), Vector* v){
    Vector* nv = MakeVector(GetSize(v), INT);
    for (size_t i = 0; i < GetSize(v); ++i) GetDataI(nv)[i] = f(GetDataI(v)[i]);
    return nv;
}

Vector* MapC(complex (*f)(complex), Vector* v){
    Vector* nv = MakeVector(GetSize(v), COMPLEX);
    for (size_t i = 0; i < GetSize(v); ++i) GetDataC(nv)[i] = f(GetDataC(v)[i]);
    return nv;
}

Vector* FilterI(bool (*filter)(int), Vector* v){
    Vector* nv = MakeVector(0, INT);
    for (size_t i = 0; i < GetSize(v); ++i) if (filter(GetDataI(v)[i])) PushBack(nv, &GetDataI(v)[i]);
    return nv;
}

Vector* FilterC(bool (*filter)(complex), Vector* v){
    Vector* nv = MakeVector(0, COMPLEX);
    for (size_t i = 0; i < GetSize(v); ++i) if (filter(GetDataC(v)[i])) PushBack(nv, &GetDataC(v)[i]);
    return nv;
}
void Concatenation(Vector* v1, Vector* v2){
    Eltype T1 = GetElType(v1);
    Eltype T2 = GetElType(v2);
    if (T1 != T2){
        UnknownType();
        return;
    }

    Eltype T = T1;
    if (T == INT) ConcatenationI(v1, v2);
    else if (T == COMPLEX) ConcatenationC(v1, v2);
    else UnknownType();
}

void ConcatenationI(Vector* v1, Vector* v2){
    size_t new_size = GetSize(v1) + GetSize(v2);
    size_t prev_size = GetSize(v1);
    SetSize(v1, new_size);
    SetDataRC(v1, realloc(GetDataI(v1), new_size * sizeof(int)));

    for (size_t i = prev_size, j = 0; i < new_size; ++i, ++j) GetDataI(v1)[i] = GetDataI(v2)[j];
}

void ConcatenationC(Vector* v1, Vector* v2){
    size_t new_size = GetSize(v1) + GetSize(v2);
    size_t prev_size = GetSize(v1);
    SetSize(v1, new_size);
    SetDataRC(v1, realloc(GetDataC(v1), new_size * sizeof(complex)));

    for (size_t i = prev_size, j = 0; i < new_size; ++i, ++j) GetDataC(v1)[i] = GetDataC(v2)[j];
}

// *** Complex Functions ***

complex IncReal(complex c) { return *MakeComplex(GetReal(&c) + 1, GetImag(&c)); }
complex IncImag(complex c) { return *MakeComplex(GetReal(&c), GetImag(&c) + 1); }
complex DecReal(complex c) { return *MakeComplex(GetReal(&c) - 1, GetImag(&c)); }
complex DecImag(complex c) { return *MakeComplex(GetReal(&c), GetImag(&c) - 1); }

// *** Int Functions ***

int IncI(int x) { return x + 1; }
int DecI(int x) { return x - 1;}
int AbsoluteI(int x) { return abs(x); }
bool IsGreaterThan0(int x) { return (x > 0 ? 1 : 0); }
bool IsLesserThan0(int x) { return (x < 0 ? 1 : 0); }