#ifndef PINJAM_BARANG_H
#define PINJAM_BARANG_H

#include <QMainWindow>
#include <QDialog>
#include <QDebug>
#include <QtSql>
#include <QFileInfo>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QDate>
#include "mainwindow.h"


namespace Ui {
class pinjam_barang;
}

class pinjam_barang : public QDialog
{
    Q_OBJECT

public:
    explicit pinjam_barang(QWidget *parent = nullptr);
    ~pinjam_barang();

private slots:
    void checkLineEdits();
    void cari();
    void showBarang();
    void refresh();

    void on_txt_status_currentTextChanged(const QString &arg1);

    void on_pushButton_save_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_delete_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_refresh_clicked();

    void on_txt_keperluan_textChanged();

    void on_txt_jmlbrg_valueChanged(int arg1);

private:
    Ui::pinjam_barang *ui;
};

#endif // PINJAM_BARANG_H
