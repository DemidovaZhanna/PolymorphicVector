//
// Created by Vasiliy Evdokimov on 27.02.2020.
//

#include "utils.h"
#include <string.h>
#include <stdio.h>

const size_t MAXN;

void Error(char const * msg){
    printf("\n*** ERROR : %s ***\n", msg);
    exit(EXIT_FAILURE);
}

void Warning(char const * msg){
    printf("\n*** WARNING : %s ***\n", msg);
    printf("*** Try again. ***\n\n");
}

double max(double a, double b){
    return (a <= b ? b : a);
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

int convert_str_to_int(char const * s){
    int res = 0;
    int n = strlen(s);
    int p10 = 1e0;
    for (int i = 0; i < n - 1; ++i) p10 *= 10;

    for (int i = 0; i < n; ++i) res += (s[i] - '0') * p10, p10 /= 10;

    return res;
}

bool is_num(char const* s){
    int n = strlen(s);
    for (int i = 0; i < n; ++i) if (!(s[i] <= '9' && s[i] >= '0')) return false;
    return true;
}

bool is_non_negative(char const * s){
    if (s[0] == '-') return false;
    return true;
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
