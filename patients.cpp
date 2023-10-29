#include "patients.h"
#include "ui_patients.h"
#include "homepage.h"

Homepage *home2;

Patients::Patients(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Patients)
{
    ui->setupUi(this);
    setWindowTitle("Patients");
    setFixedSize(QSize(800, 470));
}

Patients::~Patients()
{
    delete ui;
}

void Patients::on_backBtn_clicked()
{
    hide();
    home2 = new Homepage();
    home2->show();
}

void Patients::changeStackedWidgetPage(int index){
    if (ui && ui->stackedWidget) {
        ui->stackedWidget->setCurrentIndex(index);
    }
}

void Patients::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->regPat);
}

void Patients::on_backBtn_3_clicked()
{
    if(ui->maleRad->isChecked()){
        ui->maleRad->setAutoExclusive(false);
        ui->maleRad->setChecked(false);
        ui->maleRad->setAutoExclusive(true);
    }else if(ui->femaleRad->isChecked()){
        ui->femaleRad->setAutoExclusive(false);
        ui->femaleRad->setChecked(false);
        ui->femaleRad->setAutoExclusive(true);
    }

    ui->Name->clear();
    ui->age->clear();
    ui->contactNo->clear();
    ui->address->clear();
    ui->city->clear();
    ui->state->clear();
    ui->pincode->clear();
    ui->country->clear();
    ui->height->clear();
    ui->weight->clear();

    ui->stackedWidget->setCurrentWidget(ui->patients);
}


void Patients::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pDetails);
}


void Patients::on_backBtn_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->patients);
}


void Patients::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->reportDeath);
}


void Patients::on_backBtn_5_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->patients);
}


void Patients::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->discharge);
}


void Patients::on_backBtn_6_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->patients);
}


void Patients::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->allDetails);
}


void Patients::on_backBtn_7_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->patients);
}


void Patients::on_registerBtn_clicked()
{
    if(ui->maleRad->isChecked()){
        gender = "Male";
    }else if(ui->femaleRad->isChecked()){
        gender = "Female";
    }else{
        gender="";
    }

    Name = ui->Name->text().toStdString();
    age = ui->age->text().toStdString();
    contact = ui->contactNo->text().toStdString();

    address = ui->address->toPlainText().toStdString();
    replace(address.begin(), address.end(), ',', ' ');

    city = ui->city->text().toStdString();
    state = ui->state->text().toStdString();
    pin = ui->pincode->text().toStdString();
    country = ui->country->text().toStdString();
    height = ui->height->text().toStdString();
    weight = ui->weight->text().toStdString();


    if(Name == "" || age == "" || gender == "" || contact == "" || address == "" || city == "" || state == "" || pin == "" || country == "" || height == "" || weight == ""){
        msg.setIcon(QMessageBox::Critical);
        msg.setText("Please fill in every field");
        msg.setWindowTitle("Critical");
        msg.exec();
        return;
    }else{

        string filePath = "C:/Users/name/Downloads/data/patients.csv";

        int rowCount;

        ifstream CSVFile(filePath);

        if (CSVFile.is_open()){
            string line;
            vector<string> headerData;
            vector<vector<string>> data;

            if (getline(CSVFile, line)) {
                istringstream headerStream(line);
                string headerValue;
                while (getline(headerStream, headerValue, ',')) {
                    headerData.push_back(headerValue);
                }
            }

            while (getline(CSVFile, line)) {
                istringstream dataStream(line);
                string cellValue;
                vector<string> rowData;
                while (getline(dataStream, cellValue, ',')) {
                    rowData.push_back(cellValue);
                }
                data.push_back(rowData);
            }

            CSVFile.close();

            rowCount = data.size() + 1;

            ofstream outFile(filePath, ios::app);

            if (outFile.is_open()) {
                string newRow = to_string(rowCount) + "," + Name + "," + gender + "," + age + "," + contact + ","
                                + address + "`" + city + "`" + state + "`" + pin + "`" + country + ","
                                + height + "," + weight + "," + "Y";
                outFile << newRow << "\n";
                outFile.close();
            }else{
                msg.setIcon(QMessageBox::Critical);
                msg.setText("Error while registration.");
                msg.setWindowTitle("Critical");
                msg.exec();
                return;
            }
        }

        ifstream fileCheck(filePath);

        if(!fileCheck.is_open()){
            fileCheck.close();

            ofstream newcsv(filePath, ios::out);

            if (newcsv.is_open()) {

                string headers = "ID,NAME,GENDER,AGE,MOBNUMBER,ADDRESS,HEIGHT,WEIGHT,ALIVE";
                string newRow = "1," + Name + "," + gender + "," + age + "," + contact + ","
                                + address + "`" + city + "`" + state + "`" + pin + "`" + country + ","
                                + height + "," + weight + "," + "Y";

                newcsv << headers << "\n";
                newcsv << newRow << "\n";

                newcsv.close();
            }else {
                msg.setIcon(QMessageBox::Critical);
                msg.setText("Could Not Create CSV File.");
                msg.setWindowTitle("Critical");
                msg.exec();
                return;
            }
        }else{
            fileCheck.close();
        }


//        QFile CSVFile("C:/Users/name/Downloads/new.csv");
//        int newID = 1;
//        QStringList existingData;
//        if (CSVFile.exists()) {

//            if (CSVFile.open(QIODevice::ReadOnly | QIODevice::Text)){
//                QTextStream Stream(&CSVFile);

//                while (!Stream.atEnd()) {
//                    QString line = Stream.readLine();
//                    existingData << line;
//                    QStringList fields = line.split(",");
//                    if (fields.size() > 0) {
//                        bool ok;
//                        int id = fields[0].toInt(&ok);
//                        if (ok && id >= newID) {
//                            newID = id + 1;
//                        }
//                    }
//                }
//                CSVFile.close();
//            } else {
//                qDebug() << "Error: Could not open the CSV file for writing.";
//            }

//            if (CSVFile.open(QIODevice::Text | QIODevice::Append)) {

//                QTextStream Stream(&CSVFile);

//                QString newRow = QString::number(newID) + "," + Name + "," + gender + "," + age + "," + contact + ","
//                                 + address + "`" + city + "`" + state + "`" + pin + "`" + country + ","
//                                 + height + "," + weight + "," + "Y";


//            Stream << newRow << "\n";

//            CSVFile.close();
//            } else {
//                qDebug() << "Error: Could not open the CSV file for writing.";
//            }
//        }

//        else {

//            if (CSVFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
//                QTextStream Stream(&CSVFile);

//                QStringList headers = {"ID", "NAME", "GENDER", "AGE", "MOBNUMBER", "ADDRESS", "HEIGHT", "WEIGHT", "ALIVE"};
//                Stream << headers.join(",") << "\n";

//                QString newRow = "1," + Name + "," + gender + "," + age + "," + contact + ","
//                                 + address + "`" + city + "`" + state + "`" + pin + "`" + country + ","
//                                 + height + "," + weight + "," + "Y";

//                Stream << newRow << "\n";

//                CSVFile.close();
//            } else {
//                qDebug() << "Error: Could not create the CSV file.";
//            }
//        }

        if(ui->maleRad->isChecked()){
            ui->maleRad->setAutoExclusive(false);
            ui->maleRad->setChecked(false);
            ui->maleRad->setAutoExclusive(true);
        }else if(ui->femaleRad->isChecked()){
            ui->femaleRad->setAutoExclusive(false);
            ui->femaleRad->setChecked(false);
            ui->femaleRad->setAutoExclusive(true);
        }

        ui->Name->clear();
        ui->age->clear();
        ui->contactNo->clear();
        ui->address->clear();
        ui->city->clear();
        ui->state->clear();
        ui->pincode->clear();
        ui->country->clear();
        ui->height->clear();
        ui->weight->clear();

        msg.setIcon(QMessageBox::Information);
        msg.setText(QString::fromStdString(Name) + " registered successfully.");
        msg.setWindowTitle("Success");
        msg.exec();

    }
}

