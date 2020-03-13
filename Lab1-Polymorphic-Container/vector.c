//
// Created by Vasiliy Evdokimov on 04.03.2020.
//

#include "vector.h"

// *** Console error information ***

void UnknownType(){
    printf("\n\nERROR : Unknown type. Undefined behaviour.\n\n");
}

// *** Constructor ***

Vector* MakeVector(size_t size, Eltype eltype) {
//    size_t type_size = 0;
//    if (eltype == INT) type_size = sizeof(int);
//    else if (eltype == COMPLEX) type_size = sizeof(complex);
//    else UnknownType();
    Vector* v = (Vector*)malloc(sizeof(Vector));

    v->eltype = eltype;
    v->size = size;
    v->capacity = max(size, 100);
    if (v->eltype == INT) v->data = (int*)calloc(v->capacity, sizeof(int));
    else if (v->eltype == COMPLEX) v->data = (complex*)calloc(v->capacity, sizeof(complex));
    else UnknownType();
    return v;
};

// *** Destructor ***

void DeleteVector(Vector* v) {
    if (!v) {
        FreeData(v->data);
        FreeData(v);
    }
}

void FreeData(void* ptr) {
    free(ptr);
    ptr = NULL;
}

// *** Setters ***

void SetSize(Vector* v, size_t size) { v->size = size; }

void SetCapacity(Vector* v, size_t capacity) { v->capacity = capacity; }

void SetElement(Vector* v, size_t i, void* d) {
    Eltype T = v->eltype;
    if (T == INT) ((int*)v->data)[i] = *(int*)d;
    else if (T == COMPLEX) ((complex*)v->data)[i] = *(complex*)d;
    else UnknownType();
}

void SetData(Vector* v, void* ptr) {
    FreeData(GetData(v));
    v->data = ptr;
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

// *** Functions that change vector ***

void ExpandCapacity(Vector* v) {
    Eltype T = GetElType(v);
    if (T == INT) {
        SetCapacity(v, GetCapacity(v) * 2);
        SetData(v, (int*)realloc(GetDataI(v), GetCapacity(v) * sizeof(int)));
    }
    else if (T == COMPLEX) {
        SetCapacity(v, GetCapacity(v) * 2);
        SetData(v, (complex*)realloc(GetDataC(v), GetCapacity(v) * sizeof(complex)));
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
    size_t size = GetSize(v);
    int* new_data = GetDataI(nv);
    int* data = GetDataI(v);
    for (size_t i = 0; i < size; ++i) new_data[i] = f(data[i]);
    return nv;
}

Vector* MapC(complex (*f)(complex), Vector* v){
    Vector* nv = MakeVector(GetSize(v), COMPLEX);
    size_t size = GetSize(v);
    complex* new_data = GetDataC(nv);
    complex* data = GetDataC(v);
    for (size_t i = 0; i < size; ++i) new_data[i] = f(data[i]);
    return nv;
}

Vector* FilterI(bool (*filter)(int), Vector* v){
    Vector* nv = MakeVector(0, INT);
    size_t size = GetSize(v);
    int* data = GetDataI(v);
    for (size_t i = 0; i < size; ++i) if (filter(data[i])) PushBack(nv, &data[i]);
    return nv;
}

Vector* FilterC(bool (*filter)(complex), Vector* v){
    Vector* nv = MakeVector(0, COMPLEX);
    size_t size = GetSize(v);
    complex* data = GetDataC(v);
    for (size_t i = 0; i < size; ++i) if (filter(data[i])) PushBack(nv, &data[i]);
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
    SetData(v1, (int*)realloc(GetDataI(v1), new_size * sizeof(int)));
    int* data1 = GetDataI(v1);
    int* data2 = GetDataI(v2);
    for (size_t i = prev_size, j = 0; i < new_size; ++i, ++j) data1[i] = data2[j];
}

void ConcatenationC(Vector* v1, Vector* v2){
    size_t new_size = GetSize(v1) + GetSize(v2);
    size_t prev_size = GetSize(v1);
    SetSize(v1, new_size);
    SetData(v1, (complex*)realloc(GetDataC(v1), new_size * sizeof(complex)));
    complex* data1 = GetDataC(v1);
    complex* data2 = GetDataC(v2);
    for (size_t i = prev_size, j = 0; i < new_size; ++i, ++j) data1[i] = data2[j];
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


