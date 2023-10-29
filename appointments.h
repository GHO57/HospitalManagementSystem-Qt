#ifndef APPOINTMENTS_H
#define APPOINTMENTS_H

#include <QWidget>
#include <QMessageBox>
#include <QCoreApplication>
//#include <QFile>
//#include <QTextStream>
//#include <QString>
//#include <QStringList>
//#include <QIODevice>
//#include <QStandardItem>
#include <QStandardItemModel>
#include <QScrollBar>
#include <QSortFilterProxyModel>
#include <QRegularExpression>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace Ui {
class Appointments;
}

class Appointments : public QWidget
{
    Q_OBJECT

public:
    explicit Appointments(QWidget *parent = nullptr);
    ~Appointments();

private:
    QMessageBox msg;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
    void populateProxyModel(QString path);

private slots:
    void on_backBtn_clicked();

    void on_pushButton_clicked();

    void on_backBtn_2_clicked();

    void on_backBtn_3_clicked();

    void on_backBtn_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_submit_clicked();

    void on_regBtn_clicked();

    void on_pushButton_4_clicked();

    void on_proceed_clicked();

    void on_bookBtn_clicked();

private:
    Ui::Appointments *ui;
};

#endif // APPOINTMENTS_H
