#ifndef PATIENTS_H
#define PATIENTS_H

#include <QWidget>
#include <QMessageBox>
#include <QCoreApplication>
//#include <QFile>
//#include <QTextStream>
//#include <QString>
#include <QStringList>
//#include <QIODevice>
#include <QStandardItem>
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
class Patients;
}

class Patients : public QWidget
{
    Q_OBJECT

public:
    explicit Patients(QWidget *parent = nullptr);
    ~Patients();

private:
    string Name;
    string age;
    string gender;
    string contact;
    string address;
    string city;
    string state;
    string pin;
    string country;
    string height;
    string weight;
    QMessageBox msg;

public:
    void changeStackedWidgetPage(int index);

private slots:
    void on_backBtn_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_backBtn_3_clicked();

    void on_backBtn_4_clicked();

    void on_pushButton_5_clicked();

    void on_backBtn_5_clicked();

    void on_pushButton_6_clicked();

    void on_backBtn_6_clicked();

    void on_pushButton_7_clicked();

    void on_backBtn_7_clicked();

    void on_registerBtn_clicked();

private:
    Ui::Patients *ui;
};

#endif // PATIENTS_H
