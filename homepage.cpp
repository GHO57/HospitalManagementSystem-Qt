#include "homepage.h"
#include "./ui_homepage.h"

Homepage::Homepage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Homepage)
{
    ui->setupUi(this);
    setWindowTitle("Hospital Management System (Home Page)");
    setFixedSize(QSize(800, 470));
}

Homepage::~Homepage()
{
    delete ui;
}


void Homepage::on_appmntBtn_clicked()
{
    hide();
    appn = new Appointments();
    appn->show();
}


void Homepage::on_patientBtn_clicked()
{
    hide();
    patn = new Patients();
    patn->show();
}


void Homepage::on_DctrBtn_clicked()
{
    hide();
    doc = new Doctors();
    doc->show();
}


void Homepage::on_NrseBtn_clicked()
{
    hide();
    nurs = new Nurses();
    nurs->show();
}

