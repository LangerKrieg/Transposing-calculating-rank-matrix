#ifndef TMATRIX_H
#define TMATRIX_H

#include "rectmatrix.h"

template <class number>
class TMatrix: public TRectMatrix<number>
{
public:
    TMatrix(int , number** );
    number findDet();

private:

};

template <class number>
TMatrix<number>::TMatrix(int size_m, number** mX): TRectMatrix<number>(size_m, size_m, mX) {}

template <class number>
number TMatrix<number>::findDet() {
    int size = TRectMatrix<number>::rows;
    number** matr = TRectMatrix<number>::mA;
    if (size == 1) {
        return matr[0][0];
    }
    else if (size == 2) {
        return matr[0][0] * matr[1][1] - matr[0][1] * matr[1][0];
    }
    else {
        number det = 0;
        for (int i = 0; i < size; i++) {
            number** m = new number*[size - 1];
            for (int j = 0; j < size - 1; j++) {
                m[j] = new number[size - 1];
            }
            for (int j = 1; j < size; j++) {
                int t = 0;
                for (int k = 0; k < size; k++) {
                    if (k == i)
                        continue;
                    m[j - 1][t] = matr[j][k];
                    t++;
                }
            }
            TMatrix new_m(size - 1, m);
            int sign = 1;
            if ((i + 2) % 2 == 0) {
                sign = 1;
            }
            else {
                sign = -1;
            }
            det +=  (sign * matr[0][i] * new_m.findDet());
            for (int j = 0; j < size - 1; j++) {
                delete[] m[j];
            }
            delete [] m;
        }
        return det;
    }
}

#endif // TMATRIX_H
