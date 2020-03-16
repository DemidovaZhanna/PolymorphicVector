//
// Created by Vasiliy Evdokimov on 04.03.2020.
//

#ifndef LABA1_VECTOR_H
#define LABA1_VECTOR_H

#include <stddef.h>
#include <stdbool.h>
#include "utils.h"
#include "complex_unit.h"

typedef enum {INT, COMPLEX} Eltype;

typedef struct Vector {
    Eltype eltype;
    size_t size;
    size_t capacity;
    void* data;
} Vector;


// *** Console error information ***

void UnknownType();

// *** Constructor ***

Vector* MakeVector(size_t, Eltype);

// *** Destructor ***

void DeleteVector(Vector*);
void FreeData(void*);

// *** Setters ***

void SetSize(Vector*, size_t);
void SetCapacity(Vector*, size_t);
void SetElement(Vector*, size_t, void*);
void SetData(Vector*, void*);
void SetDataRC(Vector*, void*);

// *** Getters ***

size_t GetSize(Vector const *);
size_t GetCapacity(Vector const *);
void* GetData(Vector const *);
int* GetDataI(Vector const *);
complex* GetDataC(Vector const *);
Eltype GetElType(Vector const *);

// *** Functions that change vector ***

void ExpandCapacity(Vector*);
void PushBack(Vector*, void*);
void PushBackI(Vector*, int*);
void PushBackC(Vector*, complex*);

// *** Input and Output procedures ***

bool InputVector(Vector *);
void OutputVector(Vector*);

// *** General Functions ***

Vector* MapI(int (*)(int), Vector*);
Vector* MapC(complex (*)(complex), Vector*);
Vector* FilterI(bool (*)(int), Vector*);
Vector* FilterC(bool (*)(complex), Vector*);
void Concatenation(Vector*, Vector*);
void ConcatenationI(Vector*, Vector*);
void ConcatenationC(Vector*, Vector*);

// *** Int Functions ***

int IncI(int);
int DecI(int);
int AbsoluteI(int);
int Square(int);

// *** Int Predicates ***

bool IsGreaterThan0(int);
bool IsLesserThan0(int);
bool IsEven(int);
bool IsOdd(int);

#endif //LABA1_VECTOR_H