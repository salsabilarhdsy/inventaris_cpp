#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QDebug>
#include <QtSql>
#include <QFileInfo>
#include <QMessageBox>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase myDB;
    void connClose()
    {
        myDB.close();
        myDB.removeDatabase("D:/inventaris/inventaris.db");
    }
    bool connOpen()
    {
            myDB = QSqlDatabase::addDatabase("QSQLITE");
            myDB.setDatabaseName("D:/inventaris/inventaris.db");
            if(!myDB.open()){
                qDebug() << "No Connection to Database";
                return false;
            }else{
                qDebug() << "Database connected";
                return true;
            }
    }

public:
    explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

private slots:
    void on_pushButton_Login_clicked();

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
