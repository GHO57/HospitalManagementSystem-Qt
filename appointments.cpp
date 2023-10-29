#include "appointments.h"
#include "ui_appointments.h"
#include "homepage.h"
#include "patients.h"

Homepage *home;
Patients *patient;

Appointments::Appointments(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Appointments)
{
    ui->setupUi(this);
    setWindowTitle("Appointments");
    setFixedSize(QSize(800, 470));

    model = new QStandardItemModel(this);
    proxyModel = new QSortFilterProxyModel(this);

    ui->regBtn->setVisible(false);
    ui->comboBox->setVisible(false);
    ui->tblTitle->setVisible(false);
    ui->tableView->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->pushButton_4->setVisible(false);
    ui->matchRec->setVisible(false);
    ui->label_6->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->proceed->setVisible(false);
    ui->bookBtn->setVisible(false);
    ui->comboBox_2->setVisible(false);
    ui->comboBox_2->setMaxVisibleItems(3);
    ui->matchRec->setText("");
    ui->tableView->verticalHeader()->hide();

    populateProxyModel("C:/Users/name/Downloads/data/patients.csv");

}

void Appointments::populateProxyModel(QString path)
{
    ifstream CSVFile(path.toStdString());
    if (!CSVFile.is_open()) {
        msg.setIcon(QMessageBox::Critical);
        msg.setWindowTitle("ERROR");
        msg.setText("ERROR : SOMETHING WENT WRONG.");
        msg.exec();
        return;
    }

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

    model->setRowCount(data.size());
    model->setColumnCount(headerData.size());

    for (int col = 0; col < headerData.size(); ++col) {
        model->setHorizontalHeaderItem(col, new QStandardItem(QString::fromStdString(headerData[col])));
    }

    for (int row = 0; row < data.size(); ++row) {
        for (int col = 0; col < data[row].size(); ++col) {
            model->setItem(row, col, new QStandardItem(QString::fromStdString(data[row][col])));
        }
    }

    proxyModel->setSourceModel(model);
}


Appointments::~Appointments()
{
    delete ui;
}


void Appointments::on_backBtn_clicked()
{
    hide();
    home = new Homepage();
    home->show();
}


void Appointments::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->book);
}


void Appointments::on_backBtn_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->appointment);
}


void Appointments::on_backBtn_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->appointment);
}


void Appointments::on_backBtn_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->appointment);
}


void Appointments::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->getDetails);
}


void Appointments::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->showAll);
}

int P_id = 0;
int D_id = 0;
QString patientName = "";
QString doctorName = "";
QString doctorType = "";


void Appointments::on_submit_clicked()
{
    if(ui->yesRad->isChecked()){
        ui->regBtn->setVisible(false);
        ui->comboBox->setVisible(true);
        ui->comboBox_2->setVisible(false);
        ui->tblTitle->setVisible(true);
        ui->tableView->setVisible(true);
        ui->lineEdit->setVisible(true);
        ui->lineEdit->setText("");
        ui->pushButton_4->setVisible(true);
        ui->matchRec->setText("");
        ui->matchRec->setVisible(true);
        ui->label_6->setVisible(true);
        ui->lineEdit_2->setVisible(true);
        ui->proceed->setVisible(true);
        ui->bookBtn->setVisible(false);
        ui->tblTitle->setText("PATIENTS LIST");
        ui->label_6->setText("Enter patient's id and proceed :");
        ui->lineEdit_2->setText("");
        ui->tableView->setModel(nullptr);
        populateProxyModel("C:/Users/name/Downloads/data/patients.csv");

    }else if(ui->noRad->isChecked()){
        ui->comboBox->setVisible(false);
        ui->comboBox_2->setVisible(false);
        ui->tblTitle->setVisible(false);
        ui->tableView->setVisible(false);
        ui->pushButton_4->setVisible(false);
        ui->lineEdit->setVisible(false);
        ui->matchRec->setVisible(false);
        ui->label_6->setVisible(false);
        ui->lineEdit_2->setVisible(false);
        ui->proceed->setVisible(false);
        ui->bookBtn->setVisible(false);
        ui->regBtn->setVisible(true);
    }else{
        msg.setIcon(QMessageBox::Critical);
        msg.setWindowTitle("Critical");
        msg.setText("Please choose any one of the options.");
        msg.exec();
    }
}

void Appointments::on_regBtn_clicked()
{
    hide();
    patient = new Patients();
    patient->changeStackedWidgetPage(1);
    patient->show();
}

void Appointments::on_pushButton_4_clicked()
{

    QString searchVal = ui->lineEdit->text();;
    QString filterVal;

    if(searchVal == ""){
        msg.setIcon(QMessageBox::Critical);
        msg.setWindowTitle("Critical");
        msg.setText("Enter the Search value.");
        msg.exec();
    }else if(ui->tblTitle->text() == "PATIENTS LIST"){
        filterVal = ui->comboBox->currentText();

//        model->setRowCount(0);

//        QFile CSVFile("C:/Users/name/Downloads/downloads/hospital-management-system-main/data/patients.csv");
//        if (CSVFile.open(QIODevice::ReadOnly))
//        {
//            int lineindex = 0;
//            QTextStream Stream(&CSVFile);

//            if(!Stream.atEnd()){
//                QString headerLine = Stream.readLine();
//                QStringList headerData = headerLine.split(",");

//                for(int i=0; i < headerData.length(); i++){
//                    model->setHorizontalHeaderItem(i, new QStandardItem(headerData.at(i)));
//                }
//            }

//            while(!Stream.atEnd()){
//                QString LineData = Stream.readLine();
//                QStringList Data = LineData.split(",");

//                for(int i=0; i < Data.length(); i++){
//                    QStandardItem *item = new QStandardItem(Data.at(i));
//                    model->setItem(lineindex,i,item);
//                }
//                lineindex++;
//            }
//            CSVFile.close();
//        ifstream CSVFile("C:/Users/name/Downloads/new.csv");
//        if (!CSVFile.is_open()) {
//            msg.setIcon(QMessageBox::Critical);
//            msg.setWindowTitle("ERROR");
//            msg.setText("ERROR : File cannot be opened.");
//            msg.exec();
//            return;
//        }

//        string line;
//        vector<string> headerData;
//        vector<vector<string>> data;

//        if (getline(CSVFile, line)) {
//            istringstream headerStream(line);
//            string headerValue;
//            while (getline(headerStream, headerValue, ',')) {
//                headerData.push_back(headerValue);
//            }
//        }

//        while (getline(CSVFile, line)) {
//            istringstream dataStream(line);
//            string cellValue;
//            vector<string> rowData;
//            while (getline(dataStream, cellValue, ',')) {
//                rowData.push_back(cellValue);
//            }
//            data.push_back(rowData);
//        }

//        CSVFile.close();

//        model->setRowCount(data.size());
//        model->setColumnCount(headerData.size());

//        for (int col = 0; col < headerData.size(); ++col) {
//            model->setHorizontalHeaderItem(col, new QStandardItem(QString::fromStdString(headerData[col])));
//        }

//        for (int row = 0; row < data.size(); ++row) {
//            for (int col = 0; col < data[row].size(); ++col) {
//                model->setItem(row, col, new QStandardItem(QString::fromStdString(data[row][col])));
//            }
//        }

        populateProxyModel("C:/Users/name/Downloads/data/patients.csv");

        if(filterVal == "ID" && (searchVal.toInt() != 0)){
            proxyModel->setFilterKeyColumn(0);
            proxyModel->setFilterRegularExpression(searchVal);
            ui->tableView->setModel(proxyModel);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
            ui->tableView->horizontalHeader()->setSectionResizeMode(8, QHeaderView::Stretch);
            int rowCount = proxyModel->rowCount();
            QString records = QString::number(rowCount);
            ui->matchRec->setText(records + " matching record(s) found.");
        }else if(filterVal == "NAME"){
            QRegularExpression regExp(searchVal, QRegularExpression::CaseInsensitiveOption);
            proxyModel->setFilterKeyColumn(1);
            proxyModel->setFilterRegularExpression(regExp);
            ui->tableView->setModel(proxyModel);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
            ui->tableView->horizontalHeader()->setSectionResizeMode(8, QHeaderView::Stretch);
            int rowCount = proxyModel->rowCount();
            QString records = QString::number(rowCount);
            ui->matchRec->setText(records + " matching record(s) found.");
        }
    }
    else if(ui->tblTitle->text() == "DOCTORS LIST"){
        filterVal = ui->comboBox_2->currentText();

        //        model->setRowCount(0);

        //        QFile CSVFile("C:/Users/name/Downloads/downloads/hospital-management-system-main/data/patients.csv");
        //        if (CSVFile.open(QIODevice::ReadOnly))
        //        {
        //            int lineindex = 0;
        //            QTextStream Stream(&CSVFile);

        //            if(!Stream.atEnd()){
        //                QString headerLine = Stream.readLine();
        //                QStringList headerData = headerLine.split(",");

        //                for(int i=0; i < headerData.length(); i++){
        //                    model->setHorizontalHeaderItem(i, new QStandardItem(headerData.at(i)));
        //                }
        //            }

        //            while(!Stream.atEnd()){
        //                QString LineData = Stream.readLine();
        //                QStringList Data = LineData.split(",");

        //                for(int i=0; i < Data.length(); i++){
        //                    QStandardItem *item = new QStandardItem(Data.at(i));
        //                    model->setItem(lineindex,i,item);
        //                }
        //                lineindex++;
        //            }
        //            CSVFile.close();

        populateProxyModel("C:/Users/name/Downloads/data/doctors.csv");

        if(filterVal == "ID" && (searchVal.toInt() != 0)){
            proxyModel->setFilterKeyColumn(0);
            proxyModel->setFilterRegularExpression(searchVal);
            ui->tableView->setModel(proxyModel);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
            ui->tableView->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
            int rowCount = proxyModel->rowCount();
            QString records = QString::number(rowCount);
            ui->matchRec->setText(records + " matching record(s) found.");
        }else if(filterVal == "NAME"){
            QRegularExpression regExp(searchVal, QRegularExpression::CaseInsensitiveOption);
            proxyModel->setFilterKeyColumn(1);
            proxyModel->setFilterRegularExpression(regExp);
            ui->tableView->setModel(proxyModel);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
            ui->tableView->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
            int rowCount = proxyModel->rowCount();
            QString records = QString::number(rowCount);
            ui->matchRec->setText(records + " matching record(s) found.");
        }else if(filterVal == "TYPE"){
            QRegularExpression regExp(searchVal, QRegularExpression::CaseInsensitiveOption);
            proxyModel->setFilterKeyColumn(6);
            proxyModel->setFilterRegularExpression(regExp);
            ui->tableView->setModel(proxyModel);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
            ui->tableView->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
            int rowCount = proxyModel->rowCount();
            QString records = QString::number(rowCount);
            ui->matchRec->setText(records + " matching record(s) found.");
        }
    }
}


void Appointments::on_proceed_clicked()
{

    if(ui->lineEdit_2->text() == ""){
        msg.setIcon(QMessageBox::Critical);
        msg.setWindowTitle("Critical");
        msg.setText("Enter an id before proceeding.");
        msg.exec();
        return;
    }else if(ui->lineEdit_2->text().toInt() == 0){
        msg.setIcon(QMessageBox::Critical);
        msg.setWindowTitle("Critical");
        msg.setText("Enter a Valid id.");
        msg.exec();
        return;
    }else{
        P_id = ui->lineEdit_2->text().toInt();
        QRegularExpression regExp(QString::number(P_id), QRegularExpression::CaseInsensitiveOption);
        proxyModel->setFilterKeyColumn(0);
        proxyModel->setFilterRegularExpression(regExp);

        QModelIndex index = proxyModel->index(0, 1);
        if (index.isValid()) {
            patientName = proxyModel->data(index).toString();
            if(patientName != ""){
                populateProxyModel("C:/Users/name/Downloads/data/doctors.csv");
            }
        }else{
            msg.setIcon(QMessageBox::Warning);
            msg.setWindowTitle("Patient not Found");
            msg.setText("No patient found with the given ID.");
            msg.exec();
            return;
        }
    }

    if(P_id == ui->lineEdit_2->text().toInt()){
        ui->tableView->setModel(nullptr);
        ui->lineEdit->setText("");
        ui->lineEdit_2->setText("");
        ui->matchRec->setText("");
        ui->tblTitle->setText("DOCTORS LIST");
        ui->label_6->setText("Enter doctor's id and book    :");
        ui->comboBox->setVisible(false);
        ui->comboBox_2->setVisible(true);
        ui->proceed->setVisible(false);
        ui->bookBtn->setVisible(true);
    }

}

void Appointments::on_bookBtn_clicked()
{
    if(ui->lineEdit_2->text() == ""){
        msg.setIcon(QMessageBox::Critical);
        msg.setWindowTitle("Critical");
        msg.setText("Enter a doctor id and book appointment.");
        msg.exec();
        return;
    }
    else if(ui->lineEdit_2->text().toInt() == 0){
        msg.setIcon(QMessageBox::Critical);
        msg.setWindowTitle("Critical");
        msg.setText("Enter a Valid id.");
        msg.exec();
        return;
    }else{
        D_id = ui->lineEdit_2->text().toInt();
        QRegularExpression regExp(QString::number(D_id), QRegularExpression::CaseInsensitiveOption);
        proxyModel->setFilterKeyColumn(0);
        proxyModel->setFilterRegularExpression(regExp);

        QModelIndex index = proxyModel->index(0, 1);
        QModelIndex index2 = proxyModel->index(0, 6);
        if (index.isValid()) {
            doctorName = proxyModel->data(index).toString();
        }else{
            msg.setIcon(QMessageBox::Warning);
            msg.setWindowTitle("Doctor not Found");
            msg.setText("No doctor found with the given ID.");
            msg.exec();
            return;
        }
        if (index2.isValid()){
            doctorType = proxyModel->data(index2).toString();
        }else{
            msg.setIcon(QMessageBox::Warning);
            msg.setWindowTitle("Doctor not Found");
            msg.setText("No doctor found with the given ID.");
            msg.exec();
            return;
        }
    }

    if(D_id == ui->lineEdit_2->text().toInt()){
        ui->regBtn->setVisible(false);
        ui->comboBox->setVisible(false);
        ui->comboBox_2->setVisible(false);
        ui->tblTitle->setVisible(false);
        ui->tableView->setVisible(false);
        ui->lineEdit->setVisible(false);
        ui->pushButton_4->setVisible(false);
        ui->matchRec->setVisible(false);
        ui->label_6->setVisible(false);
        ui->lineEdit_2->setVisible(false);
        ui->proceed->setVisible(false);
        ui->bookBtn->setVisible(false);
        ui->lineEdit->setText("");
        ui->lineEdit_2->setText("");
        ui->matchRec->setText("");
        ui->tblTitle->setText("");
        ui->label_6->setText("");
        if(ui->yesRad->isChecked()){
            ui->yesRad->setAutoExclusive(false);
            ui->yesRad->setChecked(false);
            ui->yesRad->setAutoExclusive(true);
        }else if(ui->noRad->isChecked()){
            ui->noRad->setAutoExclusive(false);
            ui->noRad->setChecked(false);
            ui->noRad->setAutoExclusive(true);
        }
    }

    if(P_id != 0 && D_id != 0){
        QString pid = QString::number(P_id);
        QString did = QString::number(D_id);
        msg.setIcon(QMessageBox::Information);
        msg.setWindowTitle("SUCCESS");
        msg.setText("APPOINTMENT SUCCESSFULLY BOOKED.\n\nPATIENT : " + patientName + " (id: " + pid + ").\nDOCTOR : " + doctorName + " (id: " + did +") - " + doctorType + ".");
        msg.exec();
        return;

    }
}

