#include "logindlg.h"
#include "ui_logindlg.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlRecord>
#include <QModelIndex>
#include <QFileDialog>

Logindlg::Logindlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Logindlg)
{
    ui->setupUi(this);
    ui->Host->setText("localhost");
    ui->User->setText("root");
}

Logindlg::~Logindlg()
{
    delete ui;
}

void Logindlg::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    QString host = ui->Host->text();
    QString user = ui->User->text();
    QString pswd = ui->Pswd->text();
    QString dtbs = ui->Db->text();
    db.setHostName(host);
    db.setUserName(user);
    db.setPassword(pswd);
    db.setDatabaseName(dtbs);

    if( !db.open() )
    {
        QMessageBox::warning(this,"错误",db.lastError().text());

    } else
    {
        this->accept();
    }

}
