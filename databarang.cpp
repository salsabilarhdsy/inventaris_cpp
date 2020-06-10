#include "databarang.h"
#include "ui_databarang.h"
#include <QMessageBox>
#include <QSettings>
#include <QSqlQueryModel>

QSqlQueryModel *Barang=new QSqlQueryModel ();
QString kwd, kode_brg, nama_brg, spesifikasi, sumber_dana, kategori;

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
    connect(ui->box_sumber, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->box_kategori, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_cari, SIGNAL(textChanged(const QString&)), SLOT(cari()));

    MainWindow conn;
    conn.connOpen();
    QSqlQuery *qry=new QSqlQuery (conn.myDB);
    qry->prepare("select * from databarang");
    qry->exec();
    Barang->setQuery(*qry);
    ui->tableView->setModel(Barang);
    conn.connClose();
    qDebug() << (Barang->rowCount());

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
    qry.prepare("select * from databarang where kode_brg='"+val+"' or nama_brg='"+val+"' or spesifikasi='"+val+"' or sumber_dana='"+val+"' or kategori='"+val+"' ");

    if(qry.exec())
    {
        while(qry.next())
        {
        ui->txt_id->setText(qry.value(0).toString());
        ui->txt_nama->setText(qry.value(1).toString());
        ui->txt_spek->setText(qry.value(2).toString());
        ui->box_sumber->setCurrentText(qry.value(3).toString());
        ui->box_kategori->setCurrentText(qry.value(4).toString());
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
        if(!ui->txt_spek->text().isEmpty() && !ui->box_sumber->currentText().isEmpty() && !ui->box_kategori->currentText().isEmpty())
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

        if(!ui->txt_spek->text().isEmpty() && !ui->box_sumber->currentText().isEmpty() && !ui->box_kategori->currentText().isEmpty())
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
    nama_brg = ui->txt_nama->text();
    spesifikasi = ui->txt_spek->text();
    sumber_dana = ui->box_sumber->currentText();
    kategori = ui->box_kategori->currentText();

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
   qry.prepare("insert into databarang (nama_brg, spesifikasi, sumber_dana, kategori) values (\'"+nama_brg+"', \'"+spesifikasi+"', \'"+sumber_dana+"', \'"+kategori+"')");
    if (qry.exec())
    {
        //clear LineEdits
        refresh();

        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from databarang");
        qry->exec();
        Barang->setQuery(*qry);
        ui->tableView->setModel(Barang);
        conn.connClose();
        qDebug() << (Barang->rowCount());

        //messagebox:berhasil
        QMessageBox::information(this, tr("Save"), tr("Berhasil disimpan"));

        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }
}


void databarang::on_pushButton_edit_clicked()
{
    nama_brg = ui->txt_nama->text();
    spesifikasi = ui->txt_spek->text();
    sumber_dana = ui->box_sumber->currentText();
    kategori = ui->box_kategori->currentText();

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("update databarang set nama_brg='"+nama_brg+"', spesifikasi='"+spesifikasi+"', sumber_dana='"+sumber_dana+"', kategori='"+kategori+"' where kode_brg='"+kode_brg+"'");
    if (qry.exec())
    {
        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from databarang");
        qry->exec();
        Barang->setQuery(*qry);
        ui->tableView->setModel(Barang);
        conn.connClose();
        qDebug() << (Barang->rowCount());

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
    kode_brg = ui->txt_id->text();
    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("delete from databarang where kode_supp='"+kode_brg+"'");
    if (qry.exec())
    {
        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from databarang");
        qry->exec();
        Barang->setQuery(*qry);
        ui->tableView->setModel(Barang);
        conn.connClose();
        qDebug() << (Barang->rowCount());

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
    kwd = ui->txt_cari->text();
    MainWindow conn;
    conn.connOpen();
    if (!kwd.isEmpty())
    {
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from databarang where kode_brg='"+kwd+"' or nama_brg='"+kwd+"' or spesifikasi='"+kwd+"' or sumber_dana='"+kwd+"' or kategori='"+kwd+"' ");
        qry->exec();
        Barang->setQuery(*qry);
        ui->tableView->setModel(Barang);
        conn.connClose();
        qDebug() << (Barang->rowCount());
    }else{
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from databarang");
        qry->exec();
        Barang->setQuery(*qry);
        ui->tableView->setModel(Barang);
        conn.connClose();
        qDebug() << (Barang->rowCount());
    }
}
