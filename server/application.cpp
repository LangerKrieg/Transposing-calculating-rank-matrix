#include "application.h"

QByteArray& operator>>(QByteArray& array, double& real) {
    int p = array.indexOf(separator.toLatin1());
    if (p > 0) {
        real = atof(array.left(p));
        array = array.right(array.length() - p - 1);
    }
    return array;
}

QString& operator<<(QString& s, double c) {
    s += QString().setNum(c);
    return s;
}


TApplication::TApplication(int argc, char *argv[])
            : QCoreApplication(argc,argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10000,
                         QHostAddress("127.0.0.1"), 10001};
    comm = new TCommunicator(pars, this);

    connect(comm,SIGNAL(recieved(QByteArray)),this,SLOT(receive(QByteArray)));
}

void TApplication::receive(QByteArray msg)
{
    QString answer, s;
    int pos = msg.indexOf(separator.toLatin1());
    int sizeM = msg.left(pos).toInt();
    msg = msg.right(msg.length()-pos-1);

    pos = msg.indexOf(separator.toLatin1());
    int mode = msg.left(pos).toInt();
    msg = msg.right(msg.length()-pos-1);

    if (mode == R_MODE) {
        TRational** mA = new TRational*[sizeM];
        for(int i = 0; i < sizeM; i++) {
            mA[i] = new TRational[sizeM];
        }
        for(int i = 0; i < sizeM; i++) {
            for(int j = 0; j < sizeM; j++) {
                msg >> mA[i][j];
            }
        }
        TMatrix<TRational> M(sizeM, mA);
        pos = msg.indexOf(separator.toLatin1());
        int t = msg.left(pos).toInt();
        switch (t)
        {
            case FIND_DET_REQUEST:
                {
                    TRational det = M.findDet();
                    s += "det = ";
                    s << det;
                    answer<<QString().setNum(FIND_DET_ANSWER);
                    answer += s;
                    qDebug("det");
                    break;
                }
            case FIND_RANK_REQUEST:
                {
                    int rank = M.findRank();
                    s += QString().setNum(rank);
                    answer << QString().setNum(FIND_RANK_ANSWER);
                    answer += s;
                    qDebug("rank");
                    break;
                }
            case TRANSPOSITION_REQUEST:
                {
                    TRectMatrix<TRational> res = M.transposition();
                    s << res;
                    answer<<QString().setNum(TRANSPOSITION_ANSWER)<<s;
                    qDebug(answer.toLatin1());
                    break;
                }
            default: return;
        }
    }
    if (mode == I_MODE) {
        double** mA = new double*[sizeM];
        for(int i = 0; i < sizeM; i++) {
            mA[i] = new double[sizeM];
        }
        for(int i = 0; i < sizeM; i++) {
            for(int j = 0; j < sizeM; j++) {
                msg >> mA[i][j];
            }
        }
        TMatrix<double> M(sizeM, mA);
        pos = msg.indexOf(separator.toLatin1());
        int t = msg.left(pos).toInt();
        switch (t)
        {
            case FIND_DET_REQUEST:
                {
                    double det = M.findDet();
                    s += "det = ";
                    s << det;
                    answer<<QString().setNum(FIND_DET_ANSWER);
                    answer += s;
                    qDebug("det");
                    break;
                }
            case FIND_RANK_REQUEST:
                {
                    int rank = M.findRank();
                    s += QString().setNum(rank);
                    answer << QString().setNum(FIND_RANK_ANSWER);
                    answer += s;
                    qDebug("rank");
                    break;
                }
            case TRANSPOSITION_REQUEST:
                {
                    TRectMatrix<double> res = M.transposition();
                    s << res;
                    answer<<QString().setNum(TRANSPOSITION_ANSWER)<<s;
                    qDebug(answer.toLatin1());
                    break;
                }
            default: return;
        }
    }
    comm->send(QByteArray().append(answer.toLatin1()));
}
