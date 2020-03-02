//
// Created by Vasiliy Evdokimov on 27.02.2020.
//

#include "general_fun.h"
#include <string.h>

double max(double a, double b){
    return (a <= b ? b : a);
}

bool is_greater_than_max(char const * s, const int max) {
    int n = strlen(s);
    if (n > 10) return true;
    else if (n < 10) return false;
    else {
        int p10 = 1000000000;
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
    int p10 = 1;
    for (int i = 0; i < n - 1; ++i) p10 *= 10;

    for (int i = 0; i < n; ++i) res += (s[i] - '0') * p10, p10 /= 10;

    return res;
}