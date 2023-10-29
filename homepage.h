#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include "appointments.h"
#include "patients.h"
#include "doctors.h"
#include "nurses.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Homepage; }
QT_END_NAMESPACE

class Homepage : public QWidget
{
    Q_OBJECT

public:
    Homepage(QWidget *parent = nullptr);
    ~Homepage();

private slots:
    void on_appmntBtn_clicked();

    void on_patientBtn_clicked();

    void on_DctrBtn_clicked();

    void on_NrseBtn_clicked();

private:
    Ui::Homepage *ui;

    Appointments *appn;
    Patients *patn;
    Doctors *doc;
    Nurses *nurs;
};
#endif // HOMEPAGE_H
