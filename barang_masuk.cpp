#include "barang_masuk.h"
#include "ui_barang_masuk.h"
#include <QMessageBox>
#include <QSettings>
#include <QSqlQueryModel>

QSqlQueryModel *model=new QSqlQueryModel ();
QString idmsk, idbrg, tgl, jml, idsupp;

barang_masuk::barang_masuk(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::barang_masuk)
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
    model->setQuery(*qry);
    ui->tableView->setModel(model);
    conn.connClose();
    qDebug() << (model->rowCount());

}


barang_masuk::~barang_masuk()
{
    delete ui;
}

void barang_masuk::checkLineEdits()
{
    int jml = ui->txt_jml->value();
    if (!ui->txt_idmsk->text().isEmpty())
    {
        ui->pushButton_delete->setEnabled(true);
        if(jml!=0 && !ui->txt_idbrg->text().isEmpty() && !ui->txt_namabrg->text().isEmpty() && !ui->txt_spesifikasi->toPlainText().isEmpty() && !ui->txt_tgl->text().isEmpty() && !ui->txt_idsupp->text().isEmpty() && !ui->txt_namasupp->text().isEmpty())
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

        if(jml!=0 && !ui->txt_idbrg->text().isEmpty() && !ui->txt_namabrg->text().isEmpty() && !ui->txt_spesifikasi->toPlainText().isEmpty() && !ui->txt_tgl->text().isEmpty() && !ui->txt_idsupp->text().isEmpty() && !ui->txt_namasupp->text().isEmpty())
        {
            ui->pushButton_save->setEnabled(true);
        }else
        {
            ui->pushButton_save->setEnabled(false);
        }
    }
}

void barang_masuk::cari()
{
    QString kw;
    kw = ui->txt_cari->text();
    MainWindow conn;
    conn.connOpen();
    if (!kw.isEmpty())
    {
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from masuk_brg where id_masuk='"+kw+"' or kode_brg='"+kw+"' or tgl_masuk='"+kw+"' or jml_masuk='"+kw+"' or kode_supp='"+kw+"' ");
        qry->exec();
        model->setQuery(*qry);
        ui->tableView->setModel(model);
        conn.connClose();
        qDebug() << (model->rowCount());
    }else{
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from masuk_brg");
        qry->exec();
        model->setQuery(*qry);
        ui->tableView->setModel(model);
        conn.connClose();
        qDebug() << (model->rowCount());
    }
}

void barang_masuk::showBarang()
{
    QString kw;
    kw = ui->txt_idbrg->text();
    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    if(!kw.isEmpty()){
    qry.prepare("select * from barang where kode_brg='"+kw+"'");
        if (qry.exec())
        {
            ui->txt_namabrg->clear();
            ui->txt_spesifikasi->clear();
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

void barang_masuk::showSupplier()
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
                ui->txt_namasupp->clear();
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

void barang_masuk::on_txt_jml_valueChanged(int arg1)
{
    if(arg1==0){
        ui->pushButton_update->setEnabled(false);
        ui->pushButton_save->setEnabled(false);
    }else{
        checkLineEdits();
    }
}

void barang_masuk::refresh()
{
    ui->txt_idmsk->clear();
    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
       le->clear();
    }
    ui->txt_jml->setValue(1);
}


void barang_masuk::on_pushButton_refresh_clicked()
{
    refresh();
}


void barang_masuk::on_pushButton_save_clicked()
{
    idbrg = ui->txt_idbrg->text();
    tgl = ui->txt_tgl->text();
    jml = ui->txt_jml->text();
    idsupp = ui->txt_idsupp->text();

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into masuk_brg (kode_brg, tgl_masuk, jml_masuk, kode_supp) values ('"+idbrg+"', '"+tgl+"', '"+jml+"', '"+idsupp+"')");
    if (qry.exec())
    {

        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * masuk_brg");
        qry->exec();
        model->setQuery(*qry);
        ui->tableView->setModel(model);
        conn.connClose();
        qDebug() << (model->rowCount());

        //clear LineEdits
        refresh();

        //messagebox:berhasil
        QMessageBox::information(this, tr("Save"), tr("Berhasil disimpan"));

        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }
}

void barang_masuk::on_pushButton_update_clicked()
{
    QString id = ui->txt_idmsk->text();
    idbrg = ui->txt_idbrg->text();
    tgl = ui->txt_tgl->text();
    jml = ui->txt_jml->text();
    idsupp = ui->txt_idsupp->text();

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("update masuk_brg set kode_brg='"+idbrg+"', tgl_masuk='"+tgl+"', jml_masuk='"+jml+"', kode_supp'"+idsupp+"' where id_masuk='"+id+"'");
    if (qry.exec())
    {
        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from masuk_brg");
        qry->exec();
        model->setQuery(*qry);
        ui->tableView->setModel(model);
        conn.connClose();
        qDebug() << (model->rowCount());

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

void barang_masuk::on_pushButton_delete_clicked()
{
    idmsk = ui->txt_idmsk->text();
    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("delete from masuk_brg where id_masuk='"+idmsk+"'");
    if (qry.exec())
    {
        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from masuk_brg");
        qry->exec();
        model->setQuery(*qry);
        ui->tableView->setModel(model);
        conn.connClose();
        qDebug() << (model->rowCount());

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

void barang_masuk::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from masuk_brg where id_masuk='"+val+"' or kode_brg='"+val+"' or tgl_masuk='"+val+"' or jml_masuk='"+val+"' or kode_supp='"+val+"' ");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->txt_idmsk->setText(qry.value(0).toString());
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
