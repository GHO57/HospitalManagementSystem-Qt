#ifndef NURSES_H
#define NURSES_H

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
class Nurses;
}

class Nurses : public QWidget
{
    Q_OBJECT

public:
    explicit Nurses(QWidget *parent = nullptr);
    ~Nurses();

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
    string type;
    QMessageBox msg;

private slots:
    void on_backBtn_clicked();

    void on_pushButton_clicked();

    void on_backBtn_2_clicked();

    void on_pushButton_2_clicked();

    void on_backBtn_3_clicked();

    void on_pushButton_5_clicked();

    void on_backBtn_4_clicked();

    void on_pushButton_6_clicked();

    void on_backBtn_5_clicked();

    void on_registerBtn_clicked();

private:
    Ui::Nurses *ui;
};

#endif // NURSES_H
