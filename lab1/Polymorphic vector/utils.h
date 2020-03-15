//
// Created by Vasiliy Evdokimov on 27.02.2020.
//

#ifndef LABA1_UTILS_H
#define LABA1_UTILS_H

#include <stdbool.h>
#include <stdlib.h>

//double square(double x) { return x * x; }
double max(double, double);
bool is_greater_than_max(char const*, const int);
int convert_str_to_int(char const*);
bool is_num(char const*);
size_t read_correct_num(size_t);
void Error(char const*);
void Warning(char const*);

#endif //LABA1_UTILS_H
