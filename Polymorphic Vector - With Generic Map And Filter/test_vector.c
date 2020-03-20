//To run test_vector.c use next command in console
//gcc test_vector.c complex_unit.c vector.c utils.c -o test

#include <stdio.h>
#include <stdbool.h>
#include "vector.h"
#include "complex_unit.h"

bool IsTheSameVector(Vector* v1, Vector* v2) {
    if (GetSize(v1) != GetSize(v2)) return false;
    if (GetElType(v1) != GetElType(v2)) return false;

    Eltype T = GetElType(v1);
    size_t size = GetSize(v1);

    if (T == INT) {
        for (size_t i = 0; i < size; ++i)
            if (GetDataI(v1)[i] != GetDataI(v2)[i]) return false;
    }
    else if (T == COMPLEX){
        for (size_t i = 0; i < size; ++i)
            if ((GetReal(&GetDataC(v1)[i]) != GetReal(&GetDataC(v2)[i])) ||
            (GetImag(&GetDataC(v1)[i]) != GetImag(&GetDataC(v2)[i]))) return false;
    }
    else UnknownType();
    return true;
}


int main() {
    Vector* v1 = MakeVector(4, INT);
    Vector* v2 = MakeVector(2, INT);
    Vector* v3 = MakeVector(6, INT);
    Vector* v4 = MakeVector(3, COMPLEX);
    Vector* v5 = MakeVector(2, COMPLEX);
    Vector* v6 = MakeVector(5, COMPLEX);
    Vector* v7 = MakeVector(4, INT);
    Vector* v8 = MakeVector(3, COMPLEX);

    GetDataI(v1)[0] = 1;
    GetDataI(v1)[1] = 2;
    GetDataI(v1)[2] = 3;
    GetDataI(v1)[3] = 4;

    GetDataI(v2)[0] = 2;
    GetDataI(v2)[1] = 4;

    GetDataI(v3)[0] = 1;
    GetDataI(v3)[1] = 2;
    GetDataI(v3)[2] = 3;
    GetDataI(v3)[3] = 4;
    GetDataI(v3)[4] = 2;
    GetDataI(v3)[5] = 4;

    GetDataC(v4)[0] = *MakeComplex(1, -1);
    GetDataC(v4)[1] = *MakeComplex(2, 2);
    GetDataC(v4)[2] = *MakeComplex(-3, -3);

    GetDataC(v5)[0] = *MakeComplex(2, 2);
    GetDataC(v5)[1] = *MakeComplex(-4, 1);

    GetDataC(v6)[0] = *MakeComplex(1, -1);
    GetDataC(v6)[1] = *MakeComplex(2, 2);
    GetDataC(v6)[2] = *MakeComplex(-3, -3);
    GetDataC(v6)[3] = *MakeComplex(2, 2);
    GetDataC(v6)[4] = *MakeComplex(-4, 1);

    GetDataI(v7)[0] = 2;
    GetDataI(v7)[1] = 3;
    GetDataI(v7)[2] = 4;
    GetDataI(v7)[3] = 5;

    GetDataC(v8)[0] = *MakeComplex(2, -1);
    GetDataC(v8)[1] = *MakeComplex(3, 2);
    GetDataC(v8)[2] = *MakeComplex(-2, -3);

    if (IsTheSameVector(Filter(&IsEven, v1), v2)) printf("Test 1 : SUCCESS\n");
    else printf("Test 1 : FAIL\n");
    if (IsTheSameVector(Map(&IncI, v1), v7)) printf("Test 2 : SUCCESS\n");
    else printf("Test 2 : FAIL\n");
    Map(&DecI, v1);
    Concatenation(v1, v2);
    if (IsTheSameVector(v1, v3)) printf("Test 3 : SUCCESS\n");
    else printf("Test 3 : FAIL\n");

    if (IsTheSameVector(Filter(&IsPositiveRealAndImag, v4), Filter(&IsPositiveRealAndImag, v5))) printf("Test 4 : SUCCESS\n");
    else printf("Test 4 : FAIL\n");
    if (IsTheSameVector(Map(&IncReal, v4), v8)) printf("Test 5 : SUCCESS\n");
    else printf("Test 5 : FAIL\n");
    Concatenation(v4, v5);
    if (IsTheSameVector(v4, v6)) printf("Test 6 : SUCCESS\n");
    else printf("Test 6 : FAIL\n");
    return 0;
}
