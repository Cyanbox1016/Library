#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include <fstream>
#include <string>
#include <QDate>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tb_1->setFontFamily("SimSun");
    ui->tb_1->insertPlainText("Database connected succesfully.\n");

    model = new QSqlTableModel(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_check_in_clicked()
{
    ui->tb_1->moveCursor(QTextCursor::End);
    QString bno = ui->bno->text();
    QString bno_empty = "Book ID cannot be empty!\n";
    if (bno == "")
    {

        ui->tb_1->insertPlainText(bno_empty);
        return;
    }
    QString catgr = ui->catgr->text();
    QString title = ui->title->text();
    QString press = ui->press->text();
    int year = ui->year->text().toInt();
    QString author = ui->author->text();
    int ttl = ui->ttl->text().toInt();
    int stock = ui->stock->text().toInt();
    double price = ui->price->text().toDouble();

    QSqlQuery query;

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(QString("select * from book where bno = \'%1\';").arg(bno));
    if (model->rowCount()>=1)
    {   QSqlDatabase::database().transaction();
        bool i = query.exec(QString("delete from book where bno = \'%1\';").arg(bno));
        if (i && query.exec(QString("insert into book values(\'%1\', \'%2\', \'%3\', \'%4\', %5, \'%6\', %7, %8, %9)").arg(bno).arg(catgr).arg(title).arg(press).arg(year).arg(author).arg(price).arg(ttl).arg(stock)))
        {
            ui->tb_1->moveCursor(QTextCursor::End);
            ui->tb_1->setFontFamily("SimSun");
            ui->tb_1->insertPlainText("Update succeeded.\n");
        } else
        {
            ui->tb_1->moveCursor(QTextCursor::End);
            ui->tb_1->setFontFamily("SimSun");
            ui->tb_1->insertPlainText("Update failed.\n");
        }
        QSqlDatabase::database().commit();
    } else
    {
        if (query.exec(QString("insert into book values(\'%1\', \'%2\', \'%3\', \'%4\', %5, \'%6\', %7, %8, %9)").arg(bno).arg(catgr).arg(title).arg(press).arg(year).arg(author).arg(price).arg(ttl).arg(stock)))
        {
            ui->tb_1->moveCursor(QTextCursor::End);
            ui->tb_1->insertPlainText("Insertion succeeded.\n");
        } else
        {
            ui->tb_1->moveCursor(QTextCursor::End);
            ui->tb_1->insertPlainText("Insertion failed.\n");
        }
    }
}

void MainWindow::on_clear_2_clicked()
{
    ui->tb_1->setText("");
    ui->tb_1->moveCursor(QTextCursor::End);
}

void MainWindow::on_clear_1_clicked()
{
    ui->bno->setText("");
    ui->catgr->setText("");
    ui->title->setText("");
    ui->press->setText("");
    ui->year->setText("");
    ui->author->setText("");
    ui->price->setText("");
    ui->ttl->setText("");
    ui->stock->setText("");
}

void MainWindow::on_bno_btn_clicked()
{
    QString bno = ui->bno_ser->text();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(QString("select * from book where bno = \'%1\'").arg(bno));
    model->setHeaderData(0, Qt::Horizontal, tr("书号"));
    model->setHeaderData(1, Qt::Horizontal, tr("类目"));
    model->setHeaderData(2, Qt::Horizontal, tr("书名"));
    model->setHeaderData(3, Qt::Horizontal, tr("出版社"));
    model->setHeaderData(4, Qt::Horizontal, tr("年份"));
    model->setHeaderData(5, Qt::Horizontal, tr("作者"));
    model->setHeaderData(6, Qt::Horizontal, tr("价格"));
    model->setHeaderData(7, Qt::Horizontal, tr("总量"));
    model->setHeaderData(8, Qt::Horizontal, tr("库存"));

    QTableView *view = new QTableView;
    view->setModel(model);
    view->setGeometry(400, 400, 1050, 400);
    view->setColumnWidth(0, 100);
    view->setColumnWidth(1, 140);
    view->setColumnWidth(2, 165);
    view->setColumnWidth(3, 120);
    view->setColumnWidth(4, 80);
    view->setColumnWidth(5, 80);
    view->setColumnWidth(6, 90);
    view->setColumnWidth(7, 70);
    view->setColumnWidth(8, 70);
    view->show();
}

void MainWindow::on_bno_btn_2_clicked()
{
    QString title = ui->title_ser->text();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(QString("select * from book where title = \'%1\'").arg(title));
    model->setHeaderData(0, Qt::Horizontal, tr("书号"));
    model->setHeaderData(1, Qt::Horizontal, tr("类目"));
    model->setHeaderData(2, Qt::Horizontal, tr("书名"));
    model->setHeaderData(3, Qt::Horizontal, tr("出版社"));
    model->setHeaderData(4, Qt::Horizontal, tr("年份"));
    model->setHeaderData(5, Qt::Horizontal, tr("作者"));
    model->setHeaderData(6, Qt::Horizontal, tr("价格"));
    model->setHeaderData(7, Qt::Horizontal, tr("总量"));
    model->setHeaderData(8, Qt::Horizontal, tr("库存"));

    QTableView *view = new QTableView;
    view->setModel(model);
    view->setGeometry(400, 400, 1050, 400);
    view->setColumnWidth(0, 100);
    view->setColumnWidth(1, 140);
    view->setColumnWidth(2, 165);
    view->setColumnWidth(3, 120);
    view->setColumnWidth(4, 80);
    view->setColumnWidth(5, 80);
    view->setColumnWidth(6, 90);
    view->setColumnWidth(7, 70);
    view->setColumnWidth(8, 70);
    view->show();
}

void MainWindow::on_pushButton_clicked()
{
    QString cno = ui->cno->text();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(QString("select * from card where cno = \'%1\'").arg(cno));
    model->setHeaderData(0, Qt::Horizontal, tr("卡号"));
    model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
    model->setHeaderData(2, Qt::Horizontal, tr("部门"));
    model->setHeaderData(3, Qt::Horizontal, tr("类型"));

    QTableView *view = new QTableView;
    view->setModel(model);
    view->setGeometry(400, 400, 600, 400);
    view->show();

}



void MainWindow::on_pushButton_2_clicked()
{
    QString cno = ui->cno->text();
    QString result;

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(QString("select * from card where cno = \'%1\'").arg(cno));
    int i = model->rowCount();

    QSqlQuery query;
    if (query.exec(QString("delete from card where cno =\'%1\';").arg(cno))) {
        if (i) result = "Card deleted.\n";
        else result = "Card not found.\n";
    } else {
        result = "Deletion failed.\n";
    }

    ui->card_text->moveCursor(QTextCursor::End);
    ui->card_text->insertPlainText(result);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString cno = ui->cno_add->text();
    if(cno == "") {
        ui->card_text->moveCursor(QTextCursor::End);
        ui->card_text->insertPlainText("Cno cannot be empty.\n");
        return;
    }
    QString name = ui->name->text();
    QString dept = ui->dept_add->text();
    QString type;
    if (ui->comboBox->currentText() == "教师") {
        type = "T";
    } else if (ui->comboBox->currentText() == "学生") {
        type = "S";
    }

    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery query;
    model->setQuery(QString("select * from card where cno = \'%1\';").arg(cno));
    if (model->rowCount()>=1)
    {   QSqlDatabase::database().transaction();
        bool i = query.exec(QString("delete from card where cno = \'%1\';").arg(cno));
        if (i && query.exec(QString("insert into card values(\'%1\', \'%2\', \'%3\', \'%4\');").arg(cno).arg(name).arg(dept).arg(type)))
        {
            ui->card_text->moveCursor(QTextCursor::End);
            ui->card_text->setFontFamily("SimSun");
            ui->card_text->insertPlainText("Update succeeded.\n");
        } else
        {
            ui->card_text->moveCursor(QTextCursor::End);
            ui->card_text->setFontFamily("SimSun");
            ui->card_text->insertPlainText("Update failed.\n");
        }
        QSqlDatabase::database().commit();
    } else
    {
        if (query.exec(QString("insert into card values(\'%1\', \'%2\', \'%3\', \'%4\');").arg(cno).arg(name).arg(dept).arg(type)))
        {
            ui->card_text->moveCursor(QTextCursor::End);
            ui->card_text->insertPlainText("Insertion succeeded.\n");
        } else
        {
            ui->card_text->moveCursor(QTextCursor::End);
            ui->card_text->insertPlainText("Insertion failed.\n");
        }
    }

}



void MainWindow::on_pushButton_7_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("图书文件"), "C:\\");
    ui->textBrowser_2->setText(filename);
}

void MainWindow::on_pushButton_8_clicked()
{
    QString filename = ui->textBrowser_2->toPlainText();
    char* file;
    QByteArray byte = filename.toLatin1();
    file = byte.data();

    std::ifstream f(file);
    if (!f.is_open()) {
        ui->textBrowser_3->moveCursor(QTextCursor::End);
        ui->textBrowser_3->insertPlainText("File opening filed.\n");
        return;
    }
    ui->textBrowser_3->moveCursor(QTextCursor::End);
    ui->textBrowser_3->insertPlainText("File opening succeeded.\n");
    qint32 i = 0;
    while(!f.eof()) {
        i++;
        std::string line;
        std::getline(f, line);
        if (line == "") break;
        QString qline = QString::fromStdString(line);
        QString bno;
        QStringList list = qline.split(",");
        for (int i = 0; i < 8; i++) {
            list[i] = list[i].remove(")");
            list[i] = list[i].remove("(");
            list[i] = list[i].trimmed();
            if (i == 0) bno = list[i];
            switch(i) {
                case 4:
                    list[i].append(",");
                    break;
                case 6:
                    list[i].append(",");
                    break;
                case 7:
                    break;
                default:
                    list[i].append("\',");
                    list[i].prepend("\'");
                    break;

            }
        }
        QString value = "(";
        for (auto i : list) {
            value += i;
        }
        value += ",";
        value += list[7];
        value += ")";

        QString q = QString("insert into book values %1 ;").arg(value);
        QSqlQuery query;

        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery(QString("select * from book where bno = \'%1\';").arg(bno));
        if (model->rowCount()>=1)
        {   QSqlDatabase::database().transaction();
            bool i = query.exec(QString("delete from book where bno = \'%1\';").arg(bno));
            if (i && query.exec(q))
            {
                ui->textBrowser_3->moveCursor(QTextCursor::End);
                ui->textBrowser_3->setFontFamily("SimSun");
                ui->textBrowser_3->insertPlainText("Update succeeded.\n");
            } else
            {
                ui->textBrowser_3->moveCursor(QTextCursor::End);
                ui->textBrowser_3->setFontFamily("SimSun");
                ui->textBrowser_3->insertPlainText(QString("Insertion failed on line %1.\n").arg(i));
            }
            QSqlDatabase::database().commit();
        } else
        {
            if (query.exec(q))
            {
                ui->textBrowser_3->moveCursor(QTextCursor::End);
                ui->textBrowser_3->insertPlainText("Insertion succeeded.\n");
            } else
            {
                ui->textBrowser_3->moveCursor(QTextCursor::End);
                ui->textBrowser_3->insertPlainText(QString("Insertion failed on line %1.\n").arg(i));
            }
        }

    }
}

void MainWindow::on_pushButton_6_clicked()
{
    QString cno = ui->cno_chk->text();
    QString bno = ui->bno_chk->text();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(QString("select * from borrow where cno = \'%1\'").arg(cno));
    model->setHeaderData(0, Qt::Horizontal, tr("卡号"));
    model->setHeaderData(1, Qt::Horizontal, tr("书号"));
    model->setHeaderData(2, Qt::Horizontal, tr("借书日"));
    model->setHeaderData(3, Qt::Horizontal, tr("还书日"));

    QTableView *view = new QTableView;
    view->setModel(model);
    view->setGeometry(400, 400, 440, 400);
    view->setColumnWidth(0, 100);
    view->setColumnWidth(1, 100);
    view->setColumnWidth(2, 120);
    view->setColumnWidth(3, 120);
    view->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    QString bno = ui->bno_chk->text();
    QString cno = ui->cno_chk->text();

    QSqlQueryModel *model = new QSqlQueryModel;

    model->setQuery(QString("select * from card where cno = \'%1\';").arg(cno));
    int i1 = model->rowCount();
    model->setQuery(QString("select * from book where bno = \'%1\';").arg(bno));
    int i2 = model->rowCount();
    if (!i1) {
        ui->tb_chk->moveCursor(QTextCursor::End);
        ui->tb_chk->insertPlainText("No such card.\n");
        return;
    }
    model->setQuery(QString("select * from borrow where bno = \'%1\' and cno = \'%2\';").arg(bno).arg(cno));
    if (model->rowCount() > 0) {
        ui->tb_chk->moveCursor(QTextCursor::End);
        ui->tb_chk->insertPlainText("You have borrowed this book.\n");
        return;
    }
    if (!i2) {
        ui->tb_chk->moveCursor(QTextCursor::End);
        ui->tb_chk->insertPlainText("No such book.\n");
        return;
    }
    model->setQuery(QString("select * from book where bno = \'%1\';").arg(bno));
    if (!model->index(0, 8).data().toInt()) {

        ui->tb_chk->moveCursor(QTextCursor::End);
        ui->tb_chk->insertPlainText("Out of stock.\n");
        model->setQuery(QString("select return_date from borrow where bno = \'%1\';").arg(bno));
        int neareast = model->index(0, 0).data().toInt();
        for (int i = 0; i < model->rowCount(); i++) {
            if (model->index(i, 0).data().toInt() < neareast) {
                neareast = model->index(i, 0).data().toInt();
            }
        }
        ui->tb_chk->moveCursor(QTextCursor::End);
        ui->tb_chk->insertPlainText(QString("Soonest returning date: %1").arg(neareast));
        QDate check_today = QDate::currentDate();
        int idate = check_today.year()*10000 + check_today.month()*100 + check_today.day();
        if (idate > neareast) {
            ui->tb_chk->moveCursor(QTextCursor::End);
            ui->tb_chk->insertPlainText("(past due)");
        }
        ui->tb_chk->moveCursor(QTextCursor::End);
        ui->tb_chk->insertPlainText("\n");
        return;
    }
    QDate today = QDate::currentDate();
    QDate returnday = today.addDays(31);
    qint32 itoday = today.year()*10000 + today.month()*100 + today.day();
    qint32 ireturnday = returnday.year()*10000 + returnday.month()*100 + returnday.day();
    QString value = "('" + cno + "','" + bno + "'," + QString::number(itoday) + "," + QString::number(ireturnday) + ")";
    QSqlQuery query;
    if (!query.exec(QString("insert into borrow values %1 ;").arg(value))) {
        ui->tb_chk->moveCursor(QTextCursor::End);
        ui->tb_chk->insertPlainText("Borrowing failed.\n");
    } else {
        ui->tb_chk->moveCursor(QTextCursor::End);
        ui->tb_chk->insertPlainText("Borrowing succeeded.\n");
        query.exec(QString("update book set stock = stock-1 where bno = '%1';").arg(bno));
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    QString bno = ui->bno_chk->text();
    QString cno = ui->cno_chk->text();

    QSqlQueryModel *model = new QSqlQueryModel;

    model->setQuery(QString("select * from card where cno = \'%1\';").arg(cno));
    int i1 = model->rowCount();
    model->setQuery(QString("select * from book where bno = \'%1\';").arg(bno));
    int i2 = model->rowCount();
    if (!i1) {
        ui->tb_chk->moveCursor(QTextCursor::End);
        ui->tb_chk->insertPlainText("No such card.\n");
        return;
    }
    if (!i2) {
        ui->tb_chk->moveCursor(QTextCursor::End);
        ui->tb_chk->insertPlainText("No such book.\n");
        return;
    }
    model->setQuery(QString("select * from borrow where bno = \'%1\' and cno = '%2';").arg(bno).arg(cno));
    if (model->rowCount() == 0) {
        ui->tb_chk->moveCursor(QTextCursor::End);
        ui->tb_chk->insertPlainText("ERROR: You never borrow this book.\n");
        return;
    }
    QSqlQuery query;
    if (query.exec(QString("delete from borrow where bno = \'%1\' and cno = '%2';").arg(bno).arg(cno))) {
        query.exec(QString("update book set stock = stock + 1 where bno = '%1';").arg(bno));
        ui->tb_chk->moveCursor(QTextCursor::End);
        ui->tb_chk->insertPlainText("Returning succeeded.\n");
    } else {
        ui->tb_chk->moveCursor(QTextCursor::End);
        ui->tb_chk->insertPlainText("Returning failed.\n");
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    QString title, cat, press, author;
    qint32 upyear, lowyear;
    qreal upprice, lowprice;
    int time = 0;
    QString q = "select * from book ";

    title = ui->ser_bno->text();
    if (title != "") {
        q += QString("where title = '%1' ").arg(title);
        time++;
    }

    cat = ui->ser_cat->text();
    if (cat != "") {
        if (!time) {
            q += "where ";
        } else {
            q += "and ";
        }
        q += QString("category = '%1' ").arg(cat);
        time++;
    }

    press = ui->ser_pre->text();
    if (press != "") {
        if (!time) {
            q += "where ";
        } else {
            q += "and ";
        }
        q += QString("press = '%1' ").arg(press);
        time++;
    }

    author = ui->ser_aut->text();
    if (author != "") {
        if (!time) {
            q += "where ";
        } else {
            q += "and ";
        }
        q += QString("author = '%1' ").arg(author);
        time++;
    }

    QString buf = ui->ser_year_1->text();
    if (buf != "") {
        lowyear = buf.toInt();
        if (!time) {
            q += "where ";
        } else {
            q += "and ";
        }
        q += QString("year >= %1 ").arg(lowyear);
        time++;
    }

    buf = ui->ser_year_2->text();
        if (buf != "") {
            upyear = buf.toInt();
            if (!time) {
                q += "where ";
            } else {
                q += "and ";
            }
            q += QString("year <= %1 ").arg(upyear);
            time++;
        }

    buf = ui->ser_pri_1->text();
        if (buf != "") {
            lowprice = buf.toDouble();
            if (!time) {
                q += "where ";
            } else {
                q += "and ";
            }
            q += QString("price >= %1 ").arg(lowprice);
            time++;
        }

    buf = ui->ser_pri_2->text();
        if (buf != "") {
            upprice = buf.toDouble();
            if (!time) {
                q += "where ";
            } else {
                q += "and ";
            }
            q += QString("price <= %1 ").arg(upprice);
            time++;
        }
    q += ";";

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(q);
    model->setHeaderData(0, Qt::Horizontal, tr("书号"));
    model->setHeaderData(1, Qt::Horizontal, tr("类目"));
    model->setHeaderData(2, Qt::Horizontal, tr("书名"));
    model->setHeaderData(3, Qt::Horizontal, tr("出版社"));
    model->setHeaderData(4, Qt::Horizontal, tr("年份"));
    model->setHeaderData(5, Qt::Horizontal, tr("作者"));
    model->setHeaderData(6, Qt::Horizontal, tr("价格"));
    model->setHeaderData(7, Qt::Horizontal, tr("总量"));
    model->setHeaderData(8, Qt::Horizontal, tr("库存"));

    QTableView *view = new QTableView;
    view->setModel(model);
    view->setGeometry(400, 400, 1050, 400);
    view->setColumnWidth(0, 100);
    view->setColumnWidth(1, 140);
    view->setColumnWidth(2, 165);
    view->setColumnWidth(3, 120);
    view->setColumnWidth(4, 80);
    view->setColumnWidth(5, 80);
    view->setColumnWidth(6, 90);
    view->setColumnWidth(7, 70);
    view->setColumnWidth(8, 70);
    view->show();
}
