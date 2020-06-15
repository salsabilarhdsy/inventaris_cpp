#include "pinjam_barang.h"
#include "ui_pinjam_barang.h"
#include <QMessageBox>
#include <QSettings>
#include <QSqlQueryModel>

QSqlQueryModel *model_pinjam=new QSqlQueryModel ();
QString status, id_pinjam, id_brg, jml_pinjam, namapeminjam, keperluan;
QDate tgl_pinjam, tgl_kembali;


pinjam_barang::pinjam_barang(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pinjam_barang)
{
    ui->setupUi(this);
    ui->pushButton_save->setEnabled(false);
    ui->pushButton_update->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
    ui->txt_jmlbrg->setValue(1);
    ui->txt_tgl2->setEnabled(false);
    ui->txt_tgl->setDate(QDate::currentDate());
    ui->txt_tgl2->setDate(QDate::currentDate());
    connect(ui->txt_idbrg, SIGNAL(textChanged(const QString&)), SLOT(showBarang()));
    connect(ui->txt_cari, SIGNAL(textChanged(const QString&)), SLOT(cari()));

    connect(ui->txt_idpinjam, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_idbrg, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_namabrg, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_spesifikasi, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_keperluan, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));
    connect(ui->txt_namapeminjam, SIGNAL(textChanged(const QString&)), SLOT(checkLineEdits()));




    MainWindow conn;
    conn.connOpen();
    QSqlQuery *qry=new QSqlQuery (conn.myDB);
    qry->prepare("select * from pinjam_brg");
    qry->exec();
    model_pinjam->setQuery(*qry);
    ui->tableView->setModel(model_pinjam);
    conn.connClose();
    qDebug() << (model_pinjam->rowCount());
}

pinjam_barang::~pinjam_barang()
{
    delete ui;
}

void pinjam_barang::on_txt_status_currentTextChanged(const QString &)
{
    if(!ui->txt_idpinjam->text().isEmpty()){
        if (ui->txt_status->currentText() == "Dikembalikan")
        {
            ui->txt_tgl2->setEnabled(true);
        }else
        {
            ui->txt_tgl2->setEnabled(false);
        }
    }else
    {
        ui->txt_tgl2->setEnabled(false);
    }
}

void pinjam_barang::on_pushButton_save_clicked()
{
    id_brg = ui->txt_idbrg->text();
    jml_pinjam = ui->txt_jmlbrg->text();
    tgl_pinjam = ui->txt_tgl->date();
    QString tgl_pinjamok = tgl_pinjam.toString();
    namapeminjam = ui->txt_namapeminjam->text();
    keperluan = ui->txt_keperluan->toPlainText();
    status = ui->txt_status->currentText();


    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into pinjam_brg (kode_brg, jml_pinjam, tgl_pinjam, tgl_kembali, nama_peminjam, keperluan, status) values ('"+id_brg+"', '"+jml_pinjam+"', '"+tgl_pinjamok+"', '-', '"+namapeminjam+"', '"+keperluan+"', '"+status+"')");
    if (qry.exec())
    {

        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from pinjam_brg");
        qry->exec();
        model_pinjam->setQuery(*qry);
        ui->tableView->setModel(model_pinjam);
        conn.connClose();
        qDebug() << (model_pinjam->rowCount());

        //messagebox:berhasil
        QMessageBox::information(this, tr("Save"), tr("Berhasil disimpan"));


        //clear LineEdits
        refresh();

        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }
}

void pinjam_barang::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from pinjam_brg where id_pinjam='"+val+"'");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->txt_idpinjam->setText(qry.value(0).toString());
            ui->txt_idbrg->setText(qry.value(1).toString());
            ui->txt_jmlbrg->setValue(qry.value(2).toInt());
            ui->txt_tgl->setDate(QDate::fromString(qry.value(3).toString()));
            ui->txt_tgl2->setDate(QDate::fromString(qry.value(4).toString()));
            ui->txt_namapeminjam->setText(qry.value(5).toString());
            ui->txt_keperluan->setText(qry.value(6).toString());
            if(qry.value(7).toString()=="Dipinjam")
            {
                ui->txt_status->setCurrentIndex(0);
            }else
            {
                ui->txt_status->setCurrentIndex(1);
            }

        }
        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"), qry.lastError().text());
    }
}

void pinjam_barang::on_pushButton_delete_clicked()
{
    QString id = ui->txt_idpinjam->text();
    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("delete from pinjam_brg where id_pinjam='"+id+"'");
    if (qry.exec())
    {

        //update table
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from pinjam_brg");
        qry->exec();
        model_pinjam->setQuery(*qry);
        ui->tableView->setModel(model_pinjam);
        conn.connClose();
        qDebug() << (model_pinjam->rowCount());

        //clear LineEdits
        refresh();

        //messagebox:berhasil
        QMessageBox::information(this, tr("Delete"), tr("Berhasil dihapus"));

        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }
}

void pinjam_barang::on_pushButton_update_clicked()
{
    QString id = ui->txt_idpinjam->text();
    id_brg = ui->txt_idbrg->text();
    jml_pinjam = ui->txt_jmlbrg->text();
    tgl_pinjam = ui->txt_tgl->date();
    QString tgl_pinjamok = tgl_pinjam.toString();
    tgl_kembali = ui->txt_tgl2->date();
    QString tgl_kembaliok = tgl_pinjam.toString();
    namapeminjam = ui->txt_namapeminjam->text();
    keperluan = ui->txt_keperluan->toPlainText();
    status = ui->txt_status->currentText();

    MainWindow conn;
    conn.connOpen();
    QSqlQuery qry;
    if (ui->txt_status->currentText() == "Dipinjam")
    {
        qry.prepare("update pinjam_brg set kode_brg='"+id_brg+"', jml_pinjam='"+jml_pinjam+"', tgl_pinjam='"+tgl_pinjamok+"', tgl_kembali='-', nama_peminjam='"+namapeminjam+"', keperluan='"+keperluan+"', status='"+status+"' where id_pinjam='"+id+"'");
        if (qry.exec())
        {
            //update table
            QSqlQuery *qry=new QSqlQuery (conn.myDB);
            qry->prepare("select * from pinjam_brg");
            qry->exec();
            model_pinjam->setQuery(*qry);
            ui->tableView->setModel(model_pinjam);
            conn.connClose();
            qDebug() << (model_pinjam->rowCount());

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

    }else
    {
        qry.prepare("update pinjam_brg set kode_brg='"+id_brg+"', jml_pinjam='"+jml_pinjam+"', tgl_pinjam='"+tgl_pinjamok+"', tgl_kembali='"+tgl_kembaliok+"', nama_peminjam='"+namapeminjam+"', keperluan='"+keperluan+"', status='"+status+"' where id_pinjam='"+id+"'");
        if (qry.exec())
        {
            //update table
            QSqlQuery *qry=new QSqlQuery (conn.myDB);
            qry->prepare("select * from pinjam_brg");
            qry->exec();
            model_pinjam->setQuery(*qry);
            ui->tableView->setModel(model_pinjam);
            conn.connClose();
            qDebug() << (model_pinjam->rowCount());

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
}

void pinjam_barang::checkLineEdits()
{
    status = ui->txt_status->currentText();
    int jml = ui->txt_jmlbrg->value();

    if (!ui->txt_idpinjam->text().isEmpty())
    {
        ui->pushButton_delete->setEnabled(true);

        if(jml!=0 && !ui->txt_idbrg->text().isEmpty() && !ui->txt_namabrg->text().isEmpty() && !ui->txt_spesifikasi->toPlainText().isEmpty() && !ui->txt_namapeminjam->text().isEmpty() && !ui->txt_keperluan->toPlainText().isEmpty() )
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

        if(jml!=0 && !ui->txt_idbrg->text().isEmpty() && !ui->txt_namabrg->text().isEmpty() && !ui->txt_spesifikasi->toPlainText().isEmpty() && status == "Dipinjam" && !ui->txt_namapeminjam->text().isEmpty() && !ui->txt_keperluan->toPlainText().isEmpty() )
        {
            ui->pushButton_save->setEnabled(true);
        }else
        {
            ui->pushButton_save->setEnabled(false);
        }
    }
}

void pinjam_barang::cari()
{
    QString kw;
    kw = ui->txt_cari->text();
    MainWindow conn;
    conn.connOpen();
    if (!kw.isEmpty())
    {
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from pinjam_brg where id_pinjam='"+kw+"' or kode_brg='"+kw+"' or jml_pinjam='"+kw+"' or status='"+kw+"' or tgl_pinjam='"+kw+"' or tgl_kembali='"+kw+"' or nama_peminjam='"+kw+"' or keperluan='"+kw+"' ");
        qry->exec();
        model_pinjam->setQuery(*qry);
        ui->tableView->setModel(model_pinjam);
        conn.connClose();
        qDebug() << (model_pinjam->rowCount());
    }else{
        QSqlQuery *qry=new QSqlQuery (conn.myDB);
        qry->prepare("select * from pinjam_brg");
        qry->exec();
        model_pinjam->setQuery(*qry);
        ui->tableView->setModel(model_pinjam);
        conn.connClose();
        qDebug() << (model_pinjam->rowCount());
    }
}

void pinjam_barang::showBarang()
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

void pinjam_barang::refresh()
{
    ui->txt_idpinjam->clear();
    ui->txt_keperluan->clear();
    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
       le->clear();
    ui->txt_jmlbrg->setValue(1);
    }
}

void pinjam_barang::on_pushButton_refresh_clicked()
{
    refresh();
    ui->txt_tgl->setDate(QDate::currentDate());
    ui->txt_tgl2->setDate(QDate::currentDate());
}

void pinjam_barang::on_txt_keperluan_textChanged()
{
    checkLineEdits();
}

void pinjam_barang::on_txt_jmlbrg_valueChanged(int arg1)
{
    if(arg1==0){
        ui->pushButton_update->setEnabled(false);
        ui->pushButton_save->setEnabled(false);
    }else{
        checkLineEdits();
    }
}
