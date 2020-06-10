#ifndef BARANG_KELUAR_H
#define BARANG_KELUAR_H

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
class barang_keluar;
}

class barang_keluar : public QDialog
{
    Q_OBJECT

public:
    explicit barang_keluar(QWidget *parent = nullptr);
    ~barang_keluar();

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
    Ui::barang_keluar *ui;
};

#endif // BARANG_KELUAR_H
