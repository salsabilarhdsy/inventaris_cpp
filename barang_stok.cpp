#include "barang_stok.h"
#include "ui_barang_stok.h"
#include <QMessageBox>
#include <QSettings>
#include <QSqlQueryModel>

QString kw_sb;
QSqlQueryModel *model_stok=new QSqlQueryModel ();

barang_stok::barang_stok(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::barang_stok)
{
    ui->setupUi(this);
    connect(ui->txt_cari, SIGNAL(textChanged(const QString&)), SLOT(cari()));

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

void barang_stok::cari()
{
    kw_sb = ui->txt_cari->text();
    MainWindow conn;
    conn.connOpen();
    if (!kw_sb.isEmpty())
    {
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from barang where kode_brg='"+kw_sb+"' or nama_brg='"+kw_sb+"' or spesifikasi='"+kw_sb+"' or kategori='"+kw_sb+"' or lokasi_brg='"+kw_sb+"' or sumber_dana='"+kw_sb+"' or stok='"+kw_sb+"' ");
        qry->exec();
        model_stok->setQuery(*qry);
        ui->tableView->setModel(model_stok);
        conn.connClose();
        qDebug() << (model_stok->rowCount());
    }else{
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from barang");
        qry->exec();
        model_stok->setQuery(*qry);
        ui->tableView->setModel(model_stok);
        conn.connClose();
        qDebug() << (model_stok->rowCount());
    }
}
