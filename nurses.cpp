#include "nurses.h"
#include "ui_nurses.h"
#include "homepage.h"

Homepage *home4;

Nurses::Nurses(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Nurses)
{
    ui->setupUi(this);
    setWindowTitle("Nurses");
    setFixedSize(QSize(800, 470));
}

Nurses::~Nurses()
{
    delete ui;
}

void Nurses::on_backBtn_clicked()
{
    hide();
    home4 = new Homepage();
    home4->show();

}


void Nurses::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->regNrs);
}


void Nurses::on_backBtn_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->nurses);
}


void Nurses::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->nrsDetails);
}


void Nurses::on_backBtn_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->nurses);
}


void Nurses::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->remNrs);
}


void Nurses::on_backBtn_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->nurses);
}


void Nurses::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->allDetails);
}


void Nurses::on_backBtn_5_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->nurses);
}


void Nurses::on_registerBtn_clicked()
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
    type = ui->type->text().toStdString();

    if(Name == "" || age == "" || gender == "" || contact == "" || address == "" || city == "" || state == "" || pin == "" || country == "" || type == ""){
        msg.setIcon(QMessageBox::Critical);
        msg.setText("Please fill in every field");
        msg.setWindowTitle("Critical");
        msg.exec();
        return;
    }else{

        string filePath = "C:/Users/name/Downloads/data/nurses.csv";

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
                                + type;
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

                string headers = "ID,NAME,GENDER,AGE,MOBNUMBER,ADDRESS,TYPE";
                string newRow = "1," + Name + "," + gender + "," + age + "," + contact + ","
                                + address + "`" + city + "`" + state + "`" + pin + "`" + country + ","
                                + type;

                newcsv << headers << "\n";
                newcsv << newRow << "\n";

                newcsv.close();
            } else {
                msg.setIcon(QMessageBox::Critical);
                msg.setText("Could Not Create CSV File.");
                msg.setWindowTitle("Critical");
                msg.exec();
                return;
            }
        }else{
            fileCheck.close();
        }

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
        ui->type->clear();

        msg.setIcon(QMessageBox::Information);
        msg.setText(QString::fromStdString(Name) + " registered successfully.");
        msg.setWindowTitle("Success");
        msg.exec();

    }
}

