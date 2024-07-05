#include "rational.h"

QChar TRational::SEPARATOR = separator;

TRational::TRational()
{
    ch = 0;
    zn = 1;
}
TRational::TRational(int a, unsigned b)
{
    ch = a;
    zn = b;
}

TRational::TRational(const int& a)
{
    ch = a;
    zn = 1;
}

TRational::TRational(const QByteArray& array)
{
    int p = array.indexOf(SEPARATOR.toLatin1());
    ch = array.left(p).toInt();
    zn = array.right(array.length() - p - 1).toInt();
}

void TRational::right ()
{
    int a = ch;
    int b = zn;
    int z;
       while (b) {
          z = a % b;
          a = b;
          b = z;
       }
    int NOD = abs(a);
    ch = ch / NOD;
    zn = zn / NOD;
}

TRational abs(TRational c)
{
    if (c.ch < 0) {
        c.ch = c.ch * (-1);
    }
    return c;
}

TRational TRational::operator* (TRational c)
{
    TRational t;
    t.ch = ch * c.ch;
    t.zn = zn * c.zn;
    t.right();
    return t;
}

TRational TRational::operator/ (TRational c)
{
    TRational t;
    t.ch = ch * c.zn;
    t.zn = zn * c.ch;
    t.right();
    return t;
}

TRational TRational::operator/= (TRational c)
{
    ch = ch * c.zn;
    zn = zn * c.ch;
    right();
    return *this;
}

TRational TRational::operator+ (TRational c)
{
    TRational t;
    t.zn = zn * c.zn;
    t.ch = ch * c.zn + c.ch * zn;
    t.right();
    return t;
}

TRational TRational::operator+= (TRational c)
{
    ch = ch * c.zn + c.ch * zn;
    zn = zn * c.zn;
    right();
    return *this;
}

TRational TRational::operator- (TRational c) {
    TRational t;
    t.zn = zn * c.zn;
    t.ch = ch * c.zn - c.ch * zn;
    t.right();
    return t;
}

TRational TRational::operator-= (TRational c) {
    ch = ch * c.zn - c.ch * zn;
    zn = zn * c.zn;
    right();
    return *this;
}

TRational TRational::operator- ()
{
    TRational t;
    t.ch = ch * (-1);
    t.zn = zn;
    t.right();
    return t;
}

bool TRational::operator==(TRational c)
{
    return (ch == c.ch) && (zn == c.zn);
}

bool TRational::operator> (double d) {
    double chisl = ch;
    return (chisl / zn) > d;
}

TRational operator* (int int_number, TRational c)
{
    TRational t;
    t.ch = int_number * c.ch;
    t.zn = c.zn;
    t.right();
    return t;
}

QString& operator<<(QString& s, TRational c) {
    if (c.ch == 0) {
        s += "0";
    } else {
        s += "(";
        s += QString().setNum(c.ch);
        s += "/";
        s += QString().setNum(c.zn);
        s += ")";
        return s;
    }
}

QByteArray& operator>>(QByteArray& array, TRational& rational) {
    int p = array.indexOf(TRational::SEPARATOR.toLatin1());
    p = array.indexOf(TRational::SEPARATOR.toLatin1(),p+1);
    if (p > 0) {
        rational = TRational(array.left(p));
        array = array.right(array.length() - p - 1);
    }
    return array;
}

void TRational::set_separator(QChar ch)
{
    SEPARATOR = ch;
}
