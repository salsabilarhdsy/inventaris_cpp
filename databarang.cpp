#include "databarang.h"
#include "ui_databarang.h"
#include <QMessageBox>
#include <QSettings>
#include <QSqlQueryModel>

QSqlQueryModel *modal=new QSqlQueryModel ();
QString kw, id_barang, nama_barang, spesifikasi, sumber_dana, kategori;

databarang::databarang(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::databarang)
{
    ui->setupUi(this);

    ui->pushButton_save->setEnabled(false);
    ui->pushButton_edit->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);

    connect(ui->txt_nama, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_spek, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_sumber, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_kategori, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_cari, SIGNAL(textChanged(const QString&)), SLOT(cari()));

    MainWindow conn;
    conn.connOpen();
    QSqlQuery *qry=new QSqlQuery (conn.myDB);
    qry->prepare("select * from databarang");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    conn.connClose();
    qDebug() << (modal->rowCount());

}

databarang::~databarang()
{
    delete ui;
}

void databarang::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from databarang where kode_supp='"+val+"' or nama_barang='"+val+"' or spesifikasi='"+val+"' or kategori='"+val+"' or sumber_dana='"+val+"' ");

    if(qry.exec())
    {
        while(qry.next())
        {
        ui->txt_id->setText(qry.value(0).toString());
        ui->txt_nama->setText(qry.value(1).toString());
        ui->txt_spek->setText(qry.value(2).toString());
        ui->txt_sumber->setText(qry.value(3).toString());
        ui->txt_kategori->setText(qry.value(4).toString());
        }
        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"), qry.lastError().text());
    }
}


void databarang::checkLineEdits()
{
    if (!ui->txt_id->text().isEmpty())
    {
        ui->pushButton_delete->setEnabled(true);
        if(!ui->txt_nama->text().isEmpty() && !ui->txt_spek->text().isEmpty() && !ui->txt_sumber->text().isEmpty() && !ui->txt_kategori->text().isEmpty())
        {
            ui->pushButton_edit->setEnabled(true);
        }else
        {
            ui->pushButton_edit->setEnabled(false);
        }
    }else
    {
        ui->pushButton_delete->setEnabled(false);
        ui->pushButton_edit->setEnabled(false);

        if(!ui->txt_nama->text().isEmpty() && !ui->txt_spek->text().isEmpty() && !ui->txt_sumber->text().isEmpty() && !ui->txt_kategori->text().isEmpty())
        {
            ui->pushButton_save->setEnabled(true);
        }else
        {
            ui->pushButton_save->setEnabled(false);
        }
    }
}


void databarang::on_pushButton_save_clicked()
{
    nama_barang = ui->txt_nama->text();
    spesifikasi = ui->txt_spek->text();
    sumber_dana = ui->txt_sumber->text();
    kategori = ui->txt_kategori->text();

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("update databarang set nama_barang='"+nama_barang+"', spesifikasi='"+spesifikasi+"', sumber_dana='"+sumber_dana+"', kategori='"+kategori+"' where kode_supp='"+id_barang+"'");
    if (qry.exec())
    {
        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from databarang");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        conn.connClose();
        qDebug() << (modal->rowCount());

        //messagebox:berhasil
        QMessageBox::information(this, tr("Save"), tr("Berhasil disimpan"));

        //clear LineEdits
        foreach(QLineEdit* le, findChildren<QLineEdit*>())
        {
           le->clear();
        }

        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }
}


void databarang::on_pushButton_edit_clicked()
{
    id_barang = ui->txt_id->text();
    nama_barang = ui->txt_nama->text();
    spesifikasi = ui->txt_spek->text();
    sumber_dana = ui->txt_sumber->text();
    kategori = ui->txt_kategori->text();

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("update databarang set nama_barang='"+nama_barang+"', spesifikasi='"+spesifikasi+"', sumber_dana='"+sumber_dana+"', kategori='"+kategori+"' where kode_supp='"+id_barang+"'");
    if (qry.exec())
    {
        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from databarang");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        conn.connClose();
        qDebug() << (modal->rowCount());

        //messagebox:berhasil
        QMessageBox::information(this, tr("Update"), tr("Berhasil diubah"));

        //clear LineEdits
        refresh();

        conn.connClose();


    }
    else
    {
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }
}

void databarang::on_pushButton_refresh_clicked()
{
    refresh();
}

void databarang::on_pushButton_delete_clicked()
{
    id_barang = ui->txt_id->text();
    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("delete from databarang where kode_supp='"+id_barang+"'");
    if (qry.exec())
    {
        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from databarang");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        conn.connClose();
        qDebug() << (modal->rowCount());

        //messagebox:berhasil
        QMessageBox::information(this, tr("Delete"), tr("Berhasil dihapus"));

        //clear LineEdits
        refresh();

        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }

}

void databarang::refresh()
{
    ui->txt_id->clear();
    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
       le->clear();
    }
}


void databarang::cari()
{
    kw = ui->txt_cari->text();
    MainWindow conn;
    conn.connOpen();
    if (!kw.isEmpty())
    {
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from databarang where kode_supp='"+kw+"' or nama_barang='"+kw+"' or spesifikasi='"+kw+"' or sumber_dana='"+kw+"' or kategori='"+kw+"' ");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        conn.connClose();
        qDebug() << (modal->rowCount());
    }else{
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from databarang");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        conn.connClose();
        qDebug() << (modal->rowCount());
    }
}
