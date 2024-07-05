#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVector>
#include <QRadioButton>

#include "../common/common.h"

class TInterface : public QWidget
{
    Q_OBJECT

    QLabel *name_size_matrix;
    QLineEdit *size_matrix;
    QVector <QVector <QLineEdit*>> matrix_ch;
    QVector <QVector <QLabel*>> matrix_del;
    QVector <QVector <QLineEdit*>> matrix_zn;

    QPushButton *determinant_btn;
    QPushButton *transposition_btn;
    QPushButton *matrix_rank_btn;
    QPushButton *print_matrix_btn;

    QRadioButton *i_mode;
    QRadioButton *r_mode;

    QLabel *output;

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

public slots:
    void edit();
    void answer(QString);

private slots:
    void formRequest();

signals:
    void request(QString);
};
#endif // TINTERFACE_H
