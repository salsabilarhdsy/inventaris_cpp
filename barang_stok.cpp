#include "barang_stok.h"
#include "ui_barang_stok.h"
#include <QMessageBox>
#include <QSettings>
#include <QSqlQueryModel>

QSqlQueryModel *model_stok=new QSqlQueryModel ();

barang_stok::barang_stok(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::barang_stok)
{
    ui->setupUi(this);
    MainWindow conn;
    conn.connOpen();
    QSqlQuery *qry=new QSqlQuery (conn.myDB);
    qry->prepare("select * from barang");
    qry->exec();
    model_stok->setQuery(*qry);
    ui->tableView->setModel(model_stok);
    conn.connClose();
    qDebug() << (model_stok->rowCount());
}

barang_stok::~barang_stok()
{
    delete ui;
}
