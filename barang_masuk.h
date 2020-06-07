#ifndef BARANG_MASUK_H
#define BARANG_MASUK_H

#include <QMainWindow>
#include <QDialog>
#include <QDebug>
#include <QtSql>
#include <QFileInfo>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QModelIndex>
#include "mainwindow.h"

namespace Ui {
class barang_masuk;
}

class barang_masuk : public QDialog
{
    Q_OBJECT

public:
    explicit barang_masuk(QWidget *parent = nullptr);
    ~barang_masuk();


private slots:
    void on_pushButton_idsupp_clicked();
    void checkLineEdits();
    void cari();
    void showBarang();
    void showSupplier();
    void refresh();
    void on_txt_jml_valueChanged(int arg1);

    void on_pushButton_refresh_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_delete_clicked();

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::barang_masuk *ui;
};



#endif // BARANG_MASUK_H
