//
// Created by Vasiliy Evdokimov on 04.03.2020.
//

#ifndef LABA1_VECTOR_H
#define LABA1_VECTOR_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "complexV.h"

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

// *** Output ***

void OutputVector(Vector*);

// *** General Functions ***

Vector* MapI(int (*)(int), Vector*);
Vector* MapC(complex (*)(complex), Vector*);
Vector* FilterI(bool (*)(int), Vector*);
Vector* FilterC(bool (*)(complex), Vector*);
void Concatenation(Vector*, Vector*);
void ConcatenationI(Vector*, Vector*);
void ConcatenationC(Vector*, Vector*);

// *** Complex Functions ***

complex IncReal(complex);
complex IncImag(complex);
complex DecReal(complex);
complex DecImag(complex);

// *** Real Functions ***

int IncI(int);
int DecI(int);
int AbsoluteI(int);
bool IsGreaterThan0(int);
bool IsLesserThan0(int);

#endif //LABA1_VECTOR_H