#ifndef COMMON_H
#define COMMON_H

#include <QString>

enum messages
{
    FIND_DET_REQUEST = 1,
    FIND_DET_ANSWER,
    FIND_RANK_REQUEST,
    FIND_RANK_ANSWER,
    TRANSPOSITION_REQUEST,
    TRANSPOSITION_ANSWER
};

enum modes {
    I_MODE = 1,
    R_MODE,
};

extern const QChar separator;
QString& operator<< (QString&,const QString&);

#endif // COMMON_H
