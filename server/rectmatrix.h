#ifndef TRECTMATRIX_H
#define TRECTMATRIX_H

#include "iostream"
#include <vector>
#include <QString>

using namespace std;

template <class number>
class TRectMatrix
{
public:
    TRectMatrix(int, int, number**);
    TRectMatrix transposition();
    int findRank();

    template <class T>
    friend QString& operator<< (QString&, TRectMatrix<T>&);


private:
    int cols;
protected:
    int rows;
    number** mA;
};

template <class number>
TRectMatrix<number>::TRectMatrix(int rows_m, int cols_m, number** mX)
{
    rows = rows_m;
    cols = cols_m;
    mA = mX;
}

template <class number>
TRectMatrix<number> TRectMatrix<number>::transposition() {
    number** res = new number*[rows];
    for(int i = 0; i < rows; i++) {
        res[i] = new number[cols];
    }
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            res[j][i] = mA[i][j];
    TRectMatrix M(rows, cols, res);
    return M;
}

template <class number>
int TRectMatrix<number>::findRank() {
    int r = rows;
    double stop = 1E-9;
    number** B = new number*[rows];
    for(int i = 0; i < rows; i++) {
        B[i] = new number[cols];
    }
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            B[j][i] = mA[i][j];
    vector<char> line_used (rows);
    for (int i = 0; i < rows; i++) {
        int j;
        for (j = 0; j < cols; j++) {
            if (!line_used[j] && abs(B[j][i]) > stop)
                break;
        }
        if (j == cols) {
            r--;
        }
        else {
            line_used[j] = true;
            for (int p = i + 1; p < rows; p++)
                B[j][p] /= B[j][i];
            for (int k = 0; k < rows; k++)
                if (k != j && abs(B[k][i]) > stop)
                    for (int p = i + 1; p < cols; p++)
                        B[k][p] -= B[j][p] * B[k][i];
        }
    }
    return r;
}

template <class number>
QString& operator<< (QString& s, TRectMatrix<number>& M)
{
    s += "Matrix:\n";
    for (int i = 0; i < M.rows; i++) {
        for (int j = 0; j < M.cols; j++) {
            s<<M.mA[i][j];
            s += " ";
        };
        s += "\n";
    };
    return s;
}

#endif // TRECTMATRIX_H
