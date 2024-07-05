#include "interface.h"

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Работа №3");
    setFixedSize(650, 500);

    name_size_matrix = new QLabel("size =", this);
    name_size_matrix->setGeometry(10, 20, 30, 25);
    size_matrix = new QLineEdit("2", this);
    size_matrix->setGeometry(50, 20, 50, 25);
    for(int i = 0, left = 20, bot = 60; i < size_matrix->text().toInt(); i++) {
        QVector <QLineEdit*>* tempVector_ch = new QVector<QLineEdit*>;
        QVector <QLabel*>* tempVector_del = new QVector<QLabel*>;
        QVector <QLineEdit*>* tempVector_zn = new QVector<QLineEdit*>;
        for (int j = 0; j < size_matrix->text().toInt(); j++) {
            QLineEdit *edit_ch = new QLineEdit("0", this);
            QLabel *label_del = new QLabel("/", this);
            QLineEdit *edit_zn = new QLineEdit("1", this);
            edit_ch->setGeometry(left, bot, 25, 25);
            label_del->setGeometry(left + 30, bot, 5, 25);
            edit_zn->setGeometry(left + 40, bot, 25, 25);
            tempVector_ch->push_back(edit_ch);
            tempVector_del->push_back(label_del);
            tempVector_zn->push_back(edit_zn);
            left += 90;
        };
        matrix_ch.push_back(*tempVector_ch);
        matrix_del.push_back(*tempVector_del);
        matrix_zn.push_back(*tempVector_zn);
        bot += 40;
        left = 20;
    };

    determinant_btn = new QPushButton("Determinant", this);
    determinant_btn->setGeometry(10,450,80,30);
    transposition_btn = new QPushButton("Transposed Matrix", this);
    transposition_btn->setGeometry(120, 450, 140, 30);
    matrix_rank_btn = new QPushButton("Rank", this);
    matrix_rank_btn->setGeometry(290,450,60,30);

    i_mode = new QRadioButton("Вещественные", this);
    i_mode->setGeometry(380, 450, 100, 30);
    r_mode = new QRadioButton("Рациональные", this);
    r_mode->setGeometry(510, 450, 100, 30);
    i_mode->setChecked(true);

    output = new QLabel(this);
    output->setGeometry(50,200,200,200);

    connect(size_matrix, SIGNAL(editingFinished()), this, SLOT(edit()));
    connect(determinant_btn, SIGNAL(pressed()), this, SLOT(formRequest()));
    connect(transposition_btn, SIGNAL(pressed()), this, SLOT(formRequest()));
    connect(matrix_rank_btn, SIGNAL(pressed()), this, SLOT(formRequest()));

}

TInterface::~TInterface()
{
    delete name_size_matrix;
    delete size_matrix;

    delete determinant_btn;
    delete transposition_btn;
    delete matrix_rank_btn;

    delete i_mode;
    delete r_mode;

    delete output;

    while(matrix_ch.size() > 0) {
        for(int j = 0; j < matrix_ch.size(); j++) {
            delete matrix_ch[matrix_ch.size() - 1][j];
            delete matrix_del[matrix_del.size() - 1][j];
            delete matrix_zn[matrix_zn.size() - 1][j];
        }
        matrix_ch.remove(matrix_ch.size() - 1);
        matrix_del.remove(matrix_del.size() - 1);
        matrix_zn.remove(matrix_zn.size() - 1);
    }
}

void TInterface::edit()
{
    int lastSize = matrix_ch.size();
    int currentSize = size_matrix->text().toInt();
    if (currentSize > lastSize) {
        for(int i = 0, left = 20, bot = 60 + 40 * lastSize; i < currentSize - lastSize; i++) {
            QVector <QLineEdit*>* tempVector_ch = new QVector<QLineEdit*>;
            QVector <QLabel*>* tempVector_del = new QVector<QLabel*>;
            QVector <QLineEdit*>* tempVector_zn = new QVector<QLineEdit*>;
            for (int j = 0; j < currentSize; j++) {
                QLineEdit *edit_ch = new QLineEdit("0", this);
                QLabel *label_del = new QLabel("/", this);
                QLineEdit *edit_zn = new QLineEdit("1", this);
                tempVector_ch->push_back(edit_ch);
                tempVector_del->push_back(label_del);
                tempVector_zn->push_back(edit_zn);
                edit_ch->setGeometry(left, bot, 25, 25);
                label_del->setGeometry(left + 30, bot, 5, 25);
                edit_zn->setGeometry(left + 40, bot, 25, 25);
                edit_ch->show();
                label_del->show();
                edit_zn->show();
                left += 90;
            };
            bot += 40;
            left = 20;
            matrix_ch.push_back(*tempVector_ch);
            matrix_del.push_back(*tempVector_del);
            matrix_zn.push_back(*tempVector_zn);
        };
        for(int i = 0, left = 20 + 90 * lastSize, bot = 60; i < lastSize; i++) {
            for (int j = lastSize; j < currentSize; j++) {
                QLineEdit *edit_ch = new QLineEdit("0", this);
                QLabel *label_del = new QLabel("/", this);
                QLineEdit *edit_zn = new QLineEdit("1", this);
                edit_ch->setGeometry(left, bot, 25, 25);
                label_del->setGeometry(left + 30, bot, 5, 25);
                edit_zn->setGeometry(left + 40, bot, 25, 25);
                edit_ch->show();
                label_del->show();
                edit_zn->show();
                matrix_ch[i].push_back(edit_ch);
                matrix_del[i].push_back(label_del);
                matrix_zn[i].push_back(edit_zn);
                left += 90;
            };
            bot += 40;
            left = 20 + 90 * lastSize;
        };
    } else if(currentSize < lastSize) {
        while(matrix_ch.size() > currentSize) {
            for(int j = 0; j < lastSize; j++) {
                delete matrix_ch[matrix_ch.size() - 1][j];
                delete matrix_del[matrix_del.size() - 1][j];
                delete matrix_zn[matrix_zn.size() - 1][j];
            }
            matrix_ch.remove(matrix_ch.size() - 1);
            matrix_del.remove(matrix_del.size() - 1);
            matrix_zn.remove(matrix_zn.size() - 1);
        }
        for(int i = 0; i < matrix_ch.size(); i++) {
            for(int j = currentSize; j < lastSize; j++) {
                delete matrix_ch[i][matrix_ch[i].size() - 1];
                matrix_ch[i].pop_back();
                delete matrix_del[i][matrix_del[i].size() - 1];
                matrix_del[i].pop_back();
                delete matrix_zn[i][matrix_zn[i].size() - 1];
                matrix_zn[i].pop_back();
            }
        }
    };
}

void TInterface::formRequest()
{
    QString msg;
    int size = size_matrix->text().toInt();
    msg << size_matrix->text();

    if (i_mode->isChecked()) {
        msg << QString().setNum(I_MODE);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                msg << matrix_ch[i].value(j)->text();
            }
        };
    } else {
        msg << QString().setNum(R_MODE);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                msg << matrix_ch[i].value(j)->text() << matrix_zn[i].value(j)->text();
            }
        };
    }

    QPushButton *btn = (QPushButton*)sender();
    if (btn == determinant_btn) {
        msg << QString().setNum(FIND_DET_REQUEST);
    }
    if (btn == matrix_rank_btn) {
        msg << QString().setNum(FIND_RANK_REQUEST);
    }
    if (btn == transposition_btn) {
        msg << QString().setNum(TRANSPOSITION_REQUEST);
    }
    emit request(msg);
}

void TInterface::answer(QString msg) {
    QString text;
    int p = msg.indexOf(separator);
    int t = msg.left(p).toInt();
    switch (t) {
        case FIND_DET_ANSWER:
            text += msg.right(msg.length()-p-1);
            output->setText(text);
            break;
        case FIND_RANK_ANSWER:
            text += msg.right(msg.length()-p-1);
            output->setText(text);
            break;
        case TRANSPOSITION_ANSWER:
            msg = msg.right(msg.length()-p-1);
            p = msg.indexOf(separator);
            text += msg.left(p);
            output->setText(text);
            break;
    }
}

//void TInterface::determinant()
//{
//    int size = size_matrix->text().toInt();
//    number** mA = new number*[size];
//    for (int i = 0; i < size; i++) {
//        mA[i] = new number[size];
//    };
//    for (int i = 0; i < size; i++) {
//        for (int j = 0; j < size; j++) {
//            number elem(matrix_ch[i].value(j)->text().toInt(), matrix_zn[i].value(j)->text().toInt());
//            mA[i][j] = elem;
//        };
//    };
//    TMatrix M(size, mA);
//    number determinant = M.findDet();
//    QString s("Determinant = ");
//    s<<determinant;
//    output->setText(s);
//    for (int i = 0; i < size; i++) {
//        delete [] mA[i];
//    };
//    delete [] mA;
//}
//void TInterface::transposition()
//{
//    int size = size_matrix->text().toInt();
//    number** mA = new number*[size];
//    for (int i = 0; i < size; i++) {
//        mA[i] = new number[size];
//    };
//    for (int i = 0; i < size; i++) {
//        for (int j = 0; j < size; j++) {
//            number elem(matrix_ch[i].value(j)->text().toInt(), matrix_zn[i].value(j)->text().toInt());
//            mA[i][j] = elem;
//        };
//    };
//    TMatrix M(size, mA);
//    TMatrix res = M.transposition();
//    QString s("Transposition ");
//    s<<res;
//    output->setText(s);
//    for (int i = 0; i < size; i++) {
//        delete [] mA[i];
//    };
//    delete [] mA;
//}
//void TInterface::rank()
//{
//    int size = size_matrix->text().toInt();
//    number** mA = new number*[size];
//    for (int i = 0; i < size; i++) {
//        mA[i] = new number[size];
//    };
//    for (int i = 0; i < size; i++) {
//        for (int j = 0; j < size; j++) {
//            number elem(matrix_ch[i].value(j)->text().toInt(), matrix_zn[i].value(j)->text().toInt());
//            mA[i][j] = elem;
//        };
//    };
//    TMatrix M(size, mA);
//    int rank = M.findRank();
//    QString s("Rank = ");
//    s+= QString().setNum(rank);
//    output->setText(s);
//    for (int i = 0; i < size; i++) {
//        delete [] mA[i];
//    };
//    delete [] mA;
//}

