#ifndef DATABARANG_H
#define DATABARANG_H

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
class databarang;
}

class databarang : public QDialog
{
    Q_OBJECT

public:
    explicit databarang(QWidget *parent = nullptr);
    ~databarang();

private slots:


    void on_tableView_activated(const QModelIndex &index);

    void checkLineEdits();
    void refresh();

    void on_pushButton_save_clicked();

    void on_pushButton_edit_clicked();

    void on_pushButton_refresh_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_refreshTable_clicked();

    void on_pushButton_cari_clicked();

    void on_txt_cari_textChanged(const QString &arg1);
    void cari();

private:
    Ui::databarang *ui;
};

#endif // DATABARANG_H
