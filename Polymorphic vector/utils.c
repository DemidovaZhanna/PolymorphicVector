//
// Created by Vasiliy Evdokimov on 27.02.2020.
//

#include "utils.h"
#include <string.h>
#include <stdio.h>

size_t const MAXN;

// *** Console Interaction ***

void Error(char const * msg){
    printf("\n*** ERROR : %s ***\n", msg);
    exit(EXIT_FAILURE);
}

void Warning(char const * msg){
    printf("\n*** WARNING : %s ***\n", msg);
    printf("*** Try again. ***\n\n");
}

// *** Predicates ***

bool is_num(char const* s){
    int n = strlen(s);
    if (n == 1 && s[0] == '-') return false;

    size_t start = 0;
    if (is_negative(s)) start = 1;
    for (size_t i = start; i < n; ++i) if (!(s[i] <= '9' && s[i] >= '0')) return false;
    return true;
}

bool is_non_negative(char const * s){
    if (s[0] == '-') return false;
    return true;
}

bool is_negative(char const * s){
    return !is_non_negative(s);
}

bool is_greater_than_max(char const * s, const int max) {
    int n = strlen(s);
    if (n > 10) return true;
    else if (n < 10) return false;
    else {
        int p10 = 1e9;
        for (int i = 0; i < n; ++i){
            if ((s[i] - '0') > (max / p10) % 10) return true;
            p10 /= 10;
        }
    }
    return false;
}

// *** Utils ***

double max(double a, double b){
    return (a <= b ? b : a);
}

int convert_str_to_int(char const * s){
    int res = 0;
    size_t n = strlen(s);
    int sign = 1;
    int start = 0;
    if (is_negative(s)) sign = -1, start = 1;

    int p10 = 1e0;
    for (size_t i = 0; i < n - (1 + start); ++i) p10 *= 10;

    for (size_t i = start; i < n; ++i) res += (s[i] - '0') * p10, p10 /= 10;

    return sign * res;
}

size_t read_correct_num(size_t delta){
    char s[100] = "";
    scanf("%s", s);

    while (!is_non_negative(s) || is_greater_than_max(s, MAXN - delta) || !is_num(s)){
        if (!is_non_negative(s)) Warning("Negative size.");
        else if (!is_num(s)) Warning("It's not a number.");
        else printf("\nWARNING : Too big size, choose less number <= %zu. TRY AGAIN\n\n", MAXN - delta);
        printf("Write down size of an array : ");
        scanf("%s", s);
    }

    return convert_str_to_int(s);
}
