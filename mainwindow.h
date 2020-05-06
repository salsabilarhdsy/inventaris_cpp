#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QDebug>
#include <QtSql>
#include <QFileInfo>
#include <QMessageBox>
#include "halaman_admin.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

private slots:
    void on_pushButton_Login_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase myDB;
    halaman_admin *halamanadmin;

};
#endif // MAINWINDOW_H
