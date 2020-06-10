#include "barang_keluar.h"
#include "ui_barang_keluar.h"
#include <QMessageBox>
#include <QSettings>
#include <QSqlQueryModel>

QSqlQueryModel *keluar_brg=new QSqlQueryModel ();
QString idlr, idbrgk, tglklr, jmlklr, idsuppklr;

barang_keluar::barang_keluar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::barang_keluar)
{
    ui->setupUi(this);
    ui->pushButton_save->setEnabled(false);
    ui->pushButton_update->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
    ui->txt_jml->setValue(1);

    connect(ui->txt_idbrg, SIGNAL(textChanged(const QString&)), SLOT(showBarang()));
    connect(ui->txt_idsupp, SIGNAL(textChanged(const QString&)), SLOT(showSupplier()));
    connect(ui->txt_idbrg, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_namabrg, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_spesifikasi, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_tgl, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_idsupp, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_namasupp, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_cari, SIGNAL(textChanged(const QString&)), SLOT(cari()));

    MainWindow conn;
    conn.connOpen();
    QSqlQuery *qry=new QSqlQuery (conn.myDB);
    qry->prepare("select * from masuk_brg");
    qry->exec();
    keluar_brg->setQuery(*qry);
    ui->tableView->setModel(keluar_brg);
    conn.connClose();
    qDebug() << (keluar_brg->rowCount());
}


barang_keluar::~barang_keluar()
{
    delete ui;
}


void barang_keluar::checkLineEdits()
{
    if (!ui->txt_idbrg->text().isEmpty())
    {
        ui->pushButton_delete->setEnabled(true);
        if(!ui->txt_idbrg->text().isEmpty() && !ui->txt_namabrg->text().isEmpty() && !ui->txt_spesifikasi->toPlainText().isEmpty() && !ui->txt_tgl->text().isEmpty() && !ui->txt_idsupp->text().isEmpty() && !ui->txt_namasupp->text().isEmpty())
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

        if(!ui->txt_idbrg->text().isEmpty() && !ui->txt_namabrg->text().isEmpty() && !ui->txt_spesifikasi->toPlainText().isEmpty() && !ui->txt_tgl->text().isEmpty() && !ui->txt_idsupp->text().isEmpty() && !ui->txt_namasupp->text().isEmpty())
        {
            ui->pushButton_save->setEnabled(true);
        }else
        {
            ui->pushButton_save->setEnabled(false);
        }
    }
}

void barang_keluar::cari()
{
    QString kw;
    kw = ui->txt_cari->text();
    MainWindow conn;
    conn.connOpen();
    if (!kw.isEmpty())
    {
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from keluar_brg where id_masuk='"+kw+"' or kode_brg='"+kw+"' or tgl_masuk='"+kw+"' or jml_masuk='"+kw+"' or kode_supp='"+kw+"' ");
        qry->exec();
        keluar_brg->setQuery(*qry);
        ui->tableView->setModel(keluar_brg);
        conn.connClose();
        qDebug() << (keluar_brg->rowCount());
    }else{
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from masuk_brg");
        qry->exec();
        keluar_brg->setQuery(*qry);
        ui->tableView->setModel(keluar_brg);
        conn.connClose();
        qDebug() << (keluar_brg->rowCount());
    }
}

void barang_keluar::showBarang()
{
    QString kw;
    kw = ui->txt_idbrg->text();
    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from barang where kode_brg='"+kw+"'");
    if(!kw.isEmpty()){
        if (qry.exec())
        {
            while(qry.next())
            {
                ui->txt_namabrg->setText(qry.value(1).toString());
                ui->txt_spesifikasi->setText(qry.value(2).toString());
            }
            conn.connClose();
        }
    }else
    {
        ui->txt_namabrg->clear();
        ui->txt_spesifikasi->clear();
    }
}

void barang_keluar::showSupplier()
{
    QString kw;
    kw = ui->txt_idsupp->text();
    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from supplier where kode_supp='"+kw+"'");
    if(!kw.isEmpty())
    {
        if (qry.exec())
            {
                while(qry.next())
                {
                    ui->txt_namasupp->setText(qry.value(1).toString());
                }
                conn.connClose();
            }
    }else
    {
        ui->txt_namasupp->clear();
    }
}

void barang_keluar::on_txt_jml_valueChanged(int arg1)
{
    if(arg1==0){
        ui->pushButton_update->setEnabled(false);
        ui->pushButton_save->setEnabled(false);
        ui->pushButton_delete->setEnabled(false);
    }else{
        checkLineEdits();
    }
}

void barang_keluar::refresh()
{
    ui->txt_idklr->clear();
    ui->txt_jml->setValue(1);
    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
       le->clear();
    }
}


void barang_keluar::on_pushButton_refresh_clicked()
{
    refresh();
}


void barang_keluar::on_pushButton_save_clicked()
{
    idlr = ui->txt_idbrg->text();
    tglklr = ui->txt_tgl->text();
    jmlklr = ui->txt_jml->text();
    idsuppklr = ui->txt_idsupp->text();

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into keluar_brg (kode_brg, tgl_masuk, jml_masuk, kode_supp) values ('"+idlr+"', '"+tglklr+"', '"+jmlklr+"', '"+idsuppklr+"')");
    if (qry.exec())
    {
        //clear LineEdits
        refresh();

        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * masuk_brg");
        qry->exec();
        keluar_brg->setQuery(*qry);
        ui->tableView->setModel(keluar_brg);
        conn.connClose();
        qDebug() << (keluar_brg->rowCount());

        //messagebox:berhasil
        QMessageBox::information(this, tr("Save"), tr("Berhasil disimpan"));

        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }
}

void barang_keluar::on_pushButton_update_clicked()
{
    idlr = ui->txt_idbrg->text();
    tglklr = ui->txt_tgl->text();
    jmlklr = ui->txt_jml->text();
    idsuppklr = ui->txt_idsupp->text();

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into keluar_brg (kode_brg, tgl_masuk, jml_masuk, kode_supp) values ('"+idlr+"', '"+tglklr+"', '"+jmlklr+"', '"+idsuppklr+"')");
    if (qry.exec())
    {
        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from supplier");
        qry->exec();
        keluar_brg->setQuery(*qry);
        ui->tableView->setModel(keluar_brg);
        conn.connClose();
        qDebug() << (keluar_brg->rowCount());

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

void barang_keluar::on_pushButton_delete_clicked()
{
    idlr = ui->txt_idklr->text();
    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("delete from keluar_brg where id_masuk='"+idlr+"'");
    if (qry.exec())
    {
        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from masuk_brg");
        qry->exec();
        keluar_brg->setQuery(*qry);
        ui->tableView->setModel(keluar_brg);
        conn.connClose();
        qDebug() << (keluar_brg->rowCount());

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

void barang_keluar::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from keluar_brg where id_masuk='"+val+"' or kode_brg='"+val+"' or tgl_masuk='"+val+"' or jml_masuk='"+val+"' or kode_supp='"+val+"' ");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->txt_idklr->setText(qry.value(0).toString());
            ui->txt_idbrg->setText(qry.value(1).toString());
            ui->txt_tgl->setDate(qry.value(2).toDate());
            ui->txt_jml->setValue(qry.value(3).toInt());
            ui->txt_idsupp->setText(qry.value(4).toString());
        }
        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"), qry.lastError().text());
    }
}
