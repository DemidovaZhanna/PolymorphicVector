
//
// Created by Vasiliy Evdokimov on 04.03.2020.
//

#include "vector.h"

size_t const DEFAULT_CAPACITY = 100;
size_t const MAXN;

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
    v->capacity = max(size, DEFAULT_CAPACITY);

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
    else Warning("Trying to free NULL pointer on Vector");
}

void FreeData(void* ptr) {
    if (ptr) { free(ptr); ptr = NULL; }
    else Warning("Trying to free NULL pointer");
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

// *** Input and Output procedures ***

void OutputVector(Vector* v){
    printf("Your vector : ");
    size_t size = GetSize(v);
    Eltype T = GetElType(v);
    if (size == 0) { printf("\n"); return; }

    if (T == INT) {
        for (size_t i = 0; i < size - 1; ++i) printf("%d  ", GetDataI(v)[i]);
        printf("%d\n", GetDataI(v)[size - 1]);
    }
    else if (T == COMPLEX) {
        for (size_t i = 0; i < size - 1; ++i) printf("%lf + %lfi  ", GetReal(&GetDataC(v)[i]), GetImag(&GetDataC(v)[i]));
        printf("%lf + %lfi\n", GetReal(&GetDataC(v)[size - 1]), GetImag(&GetDataC(v)[size - 1]));
    }
    else UnknownType();
}

bool InputVector(Vector * v){
    if (GetSize(v) == 0) { printf("\n"); return true; }

    bool is_succeeded = true;

    if (GetElType(v) == INT){
        printf("Enter %zu integer elements separated by space of your vector : ", GetSize(v));

        char elem[100] = "";
        for (size_t i = 0; i < GetSize(v); ++i) {
            scanf("%s", elem);
            if (is_greater_than_max(elem, MAXN) || !is_num(elem)) is_succeeded = false;

            if (is_succeeded) GetDataI(v)[i] = convert_str_to_int(elem);
        }
    }
    else if (GetElType(v) == COMPLEX){
        printf("Enter %zu elements \"<real> <imag>\" : ", GetSize(v));

        char real[100] = "";
        char imag[100] = "";
        for (size_t i = 0; i < GetSize(v); ++i){
            scanf("%s %s", real, imag);
            if (is_greater_than_max(real, MAXN) || is_greater_than_max(imag, MAXN) ||
                !is_num(real) || !is_num(imag)) is_succeeded = false;

            if (is_succeeded){
                SetReal(&GetDataC(v)[i], convert_str_to_int(real));
                SetImag(&GetDataC(v)[i], convert_str_to_int(imag));
            }
        }
    }
    else UnknownType();

    if (!is_succeeded) {
        if (GetElType(v) == INT) Warning("One of elements is not an integer type. Incorrect data.");
        else if (GetElType(v) == COMPLEX) Warning("One of elements is not a complex type. Incorrect data.");
    }

    return is_succeeded;
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
    if (T1 != T2) UnknownType();

    Eltype T = T1;
    if (T == INT) ConcatenationI(v1, v2);
    else if (T == COMPLEX) ConcatenationC(v1, v2);
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

// *** Int Functions ***

int IncI(int x) { return x + 1; }
int DecI(int x) { return x - 1;}
int AbsoluteI(int x) { return abs(x); }

// *** Int Predicates ***

bool IsGreaterThan0(int x) { return (x > 0 ? 1 : 0); }
bool IsLesserThan0(int x) { return (x < 0 ? 1 : 0); }
bool IsEven(int x) { return (x % 2 == 0 ? 1 : 0); }
bool IsOdd(int x) { return (x % 2 == 1 ? 1 : 0); }