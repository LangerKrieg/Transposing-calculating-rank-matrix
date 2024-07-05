#ifndef TRATIONAL_H
#define TRATIONAL_H

#include <iostream>
#include <QString>
#include "math.h"
#include "../common/common.h"
using namespace std;

class TRational
{
public:
    TRational();
    TRational(int, unsigned);
    TRational(const int&);
    TRational(const QByteArray& array);

    TRational operator* (TRational);
    TRational operator/ (TRational);
    TRational operator/= (TRational);
    TRational operator+ (TRational);
    TRational operator+= (TRational);
    TRational operator- (TRational);
    TRational operator-= (TRational);


    TRational operator- ();

    bool operator== (TRational);
    bool operator> (double);

    friend TRational operator* (int, TRational);
    friend TRational abs (TRational);
    friend QByteArray& operator>>(QByteArray&, TRational&);

    friend QString& operator<<(QString&, TRational);

    operator QString();

    void set_separator(QChar ch);

private:
    static QChar SEPARATOR;
    int ch, zn;
    void right();
};

#endif // TRATIONAL_H
