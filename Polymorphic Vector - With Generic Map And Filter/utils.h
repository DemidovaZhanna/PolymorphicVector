//
// Created by Vasiliy Evdokimov on 27.02.2020.
//

#ifndef LABA1_UTILS_H
#define LABA1_UTILS_H

#include <stdbool.h>
#include <stdlib.h>

// *** Console Interaction ***

void Error(char const*);
void Warning(char const*);

// *** Predicates ***

bool is_int(char const*);
bool is_greater_than_max(char const*, const int);
bool is_non_negative(char const*);
bool is_negative(char const*);

// *** Utils ***

double max(double, double);
int convert_str_to_int(char const*);
size_t read_correct_num(size_t);


#endif //LABA1_UTILS_H
