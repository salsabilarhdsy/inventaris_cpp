#include "supplier.h"
#include "ui_supplier.h"
#include <QMessageBox>
#include <QSettings>
#include <QSqlQueryModel>

QSqlQueryModel *modal=new QSqlQueryModel ();
QString kw, id, nama, alamat, telp, kota;

supplier::supplier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::supplier)
{
    ui->setupUi(this);

    ui->pushButton_save->setEnabled(false);
    ui->pushButton_update->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);

    connect(ui->txt_nama, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_alamat, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_kota, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_telp, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_cari, SIGNAL(textChanged(const QString&)), SLOT(cari()));

    MainWindow conn;
    conn.connOpen();
    QSqlQuery *qry=new QSqlQuery (conn.myDB);
    qry->prepare("select * from supplier");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    conn.connClose();
    qDebug() << (modal->rowCount());

}

supplier::~supplier()
{
    delete ui;
}

void supplier::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from supplier where kode_supp='"+val+"' or nama_supp='"+val+"' or alamat='"+val+"' or kota='"+val+"' or telp='"+val+"' ");

    if(qry.exec())
    {
        while(qry.next())
        {
        ui->txt_id->setText(qry.value(0).toString());
        ui->txt_nama->setText(qry.value(1).toString());
        ui->txt_alamat->setText(qry.value(2).toString());
        ui->txt_kota->setText(qry.value(3).toString());
        ui->txt_telp->setText(qry.value(4).toString());
        }
        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"), qry.lastError().text());
    }
}


void supplier::checkLineEdits()
{
    if (!ui->txt_id->text().isEmpty())
    {
        ui->pushButton_delete->setEnabled(true);
        if(!ui->txt_alamat->text().isEmpty() && !ui->txt_kota->text().isEmpty() && !ui->txt_telp->text().isEmpty())
        {
            ui->pushButton_update->setEnabled(true);
        }else
        {
            ui->pushButton_update->setEnabled(false);
        }
    }else
    {
        ui->pushButton_delete->setEnabled(false);
        ui->pushButton_update->setEnabled(false);

        if(!ui->txt_alamat->text().isEmpty() && !ui->txt_kota->text().isEmpty() && !ui->txt_telp->text().isEmpty())
        {
            ui->pushButton_save->setEnabled(true);
        }else
        {
            ui->pushButton_save->setEnabled(false);
        }
    }
}


void supplier::on_pushButton_save_clicked()
{
    nama = ui->txt_nama->text();
    alamat = ui->txt_alamat->text();
    telp = ui->txt_telp->text();
    kota = ui->txt_kota->text();

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into supplier (nama_supp, alamat, kota, telp) values ('"+nama+"', '"+alamat+"', '"+kota+"', '"+telp+"')");
    if (qry.exec())
    {
        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from supplier");
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


void supplier::on_pushButton_update_clicked()
{
    id = ui->txt_id->text();
    nama = ui->txt_nama->text();
    alamat = ui->txt_alamat->text();
    telp = ui->txt_telp->text();
    kota = ui->txt_kota->text();

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("update supplier set nama_supp='"+nama+"', alamat='"+alamat+"', kota='"+kota+"', telp='"+telp+"' where kode_supp='"+id+"'");
    if (qry.exec())
    {
        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from supplier");
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

void supplier::on_pushButton_refresh_clicked()
{
    refresh();
}

void supplier::on_pushButton_delete_clicked()
{
    id = ui->txt_id->text();
    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("delete from supplier where kode_supp='"+id+"'");
    if (qry.exec())
    {
        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from supplier");
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

void supplier::refresh()
{
    ui->txt_id->clear();
    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
       le->clear();
    }
}


void supplier::cari()
{
    kw = ui->txt_cari->text();
    MainWindow conn;
    conn.connOpen();
    if (!kw.isEmpty())
    {
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from supplier where kode_supp='"+kw+"' or nama_supp='"+kw+"' or alamat='"+kw+"' or kota='"+kw+"' or telp='"+kw+"' ");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        conn.connClose();
        qDebug() << (modal->rowCount());
    }else{
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from supplier");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        conn.connClose();
        qDebug() << (modal->rowCount());
    }
}
