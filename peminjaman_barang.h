#ifndef PEMINJAMAN_BARANG_H
#define PEMINJAMAN_BARANG_H

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
class peminjaman_barang;
}

class peminjaman_barang : public QDialog
{
    Q_OBJECT

public:
    explicit peminjaman_barang(QWidget *parent = nullptr);
    ~peminjaman_barang();

private:
    Ui::peminjaman_barang *ui;
};

#endif // PEMINJAMAN_BARANG_H
