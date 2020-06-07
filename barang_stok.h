#ifndef BARANG_STOK_H
#define BARANG_STOK_H

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
class barang_stok;
}

class barang_stok : public QDialog
{
    Q_OBJECT

public:
    explicit barang_stok(QWidget *parent = nullptr);
    ~barang_stok();

private:
    Ui::barang_stok *ui;
};

#endif // BARANG_STOK_H
