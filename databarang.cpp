#include "databarang.h"
#include "ui_databarang.h"
#include <QMessageBox>
#include <QSettings>
#include <QSqlQueryModel>

QSqlQueryModel *Barang=new QSqlQueryModel ();
QString kwd, kode_brg, nama_brg, spesifikasi, sumber_dana, kategori, lokasi;

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
    connect(ui->txt_lokasi, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_dana, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_kategori, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_cari, SIGNAL(textChanged(const QString&)), SLOT(cari()));

    MainWindow conn;
    conn.connOpen();
    QSqlQuery *qry=new QSqlQuery (conn.myDB);
    qry->prepare("select kode_brg, nama_brg, spesifikasi, kategori, lokasi_brg, sumber_dana from barang");
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
    qry.prepare("select * from barang where kode_brg='"+val+"'");

    if(qry.exec())
    {
        while(qry.next())
        {
            ui->txt_id->setText(qry.value(0).toString());
            ui->txt_nama->setText(qry.value(1).toString());
            ui->txt_spek->setText(qry.value(2).toString());
            ui->txt_kategori->setText(qry.value(3).toString());
            ui->txt_lokasi->setText(qry.value(4).toString());
            ui->txt_dana->setText(qry.value(5).toString());
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
        if(!ui->txt_nama->text().isEmpty() && !ui->txt_spek->toPlainText().isEmpty() && !ui->txt_lokasi->text().isEmpty() && !ui->txt_dana->text().isEmpty() && !ui->txt_kategori->text().isEmpty())
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

        if(!ui->txt_nama->text().isEmpty() && !ui->txt_spek->toPlainText().isEmpty() && !ui->txt_lokasi->text().isEmpty() && !ui->txt_dana->text().isEmpty() && !ui->txt_kategori->text().isEmpty())
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
    spesifikasi = ui->txt_spek->toPlainText();
    sumber_dana = ui->txt_dana->text();
    kategori = ui->txt_kategori->text();
    lokasi = ui->txt_lokasi->text();

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
   qry.prepare("insert into barang (nama_brg, spesifikasi, kategori, lokasi_brg, sumber_dana, stok) values ('"+nama_brg+"', '"+spesifikasi+"', '"+kategori+"', '"+lokasi+"', '"+sumber_dana+"', 0)");
    if (qry.exec())
    {
        //clear LineEdits
        refresh();

        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select kode_brg, nama_brg, spesifikasi, kategori, lokasi_brg, sumber_dana from barang");
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
    kode_brg = ui->txt_id->text();
    nama_brg = ui->txt_nama->text();
    spesifikasi = ui->txt_spek->toPlainText();
    sumber_dana = ui->txt_dana->text();
    kategori = ui->txt_kategori->text();
    lokasi = ui->txt_lokasi->text();

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("update barang set nama_brg='"+nama_brg+"', spesifikasi='"+spesifikasi+"', lokasi_brg='"+lokasi+"', sumber_dana='"+sumber_dana+"', kategori='"+kategori+"' where kode_brg='"+kode_brg+"'");
    if (qry.exec())
    {
        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select kode_brg, nama_brg, spesifikasi, kategori, lokasi_brg, sumber_dana from barang");
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
    qry.prepare("delete from barang where kode_brg='"+kode_brg+"'");
    if (qry.exec())
    {
        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select kode_brg, nama_brg, spesifikasi, kategori, lokasi_brg, sumber_dana from barang");
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
    ui->txt_spek->clear();
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
        qry->prepare("select * from barang where kode_brg='"+kwd+"' or nama_brg='"+kwd+"' or lokasi_brg='"+kwd+"' or spesifikasi='"+kwd+"' or sumber_dana='"+kwd+"' or kategori='"+kwd+"' ");
        qry->exec();
        Barang->setQuery(*qry);
        ui->tableView->setModel(Barang);
        conn.connClose();
        qDebug() << (Barang->rowCount());
    }else{
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select kode_brg, nama_brg, spesifikasi, kategori, lokasi_brg, sumber_dana from barang");
        qry->exec();
        Barang->setQuery(*qry);
        ui->tableView->setModel(Barang);
        conn.connClose();
        qDebug() << (Barang->rowCount());
    }
}
