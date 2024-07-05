#ifndef TAPPLICATION_H
#define TAPPLICATION_H

#include <QObject>
#include <QCoreApplication>
#include <rational.h>

#include "matrix.h"
#include "../common/common.h"
#include "../common/communicator.h"

class TApplication : public QCoreApplication
{
    Q_OBJECT

    TCommunicator *comm;

public:

    TApplication(int, char**);

signals:

public slots:

    void receive(QByteArray);

};

#endif // TAPPLICATION_H
