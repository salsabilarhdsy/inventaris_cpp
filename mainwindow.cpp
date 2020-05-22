#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "halaman_admin.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}


MainWindow::~MainWindow()
{
    delete ui;
    qDebug() << "Closing the database";
    myDB.close();
}

void MainWindow::on_pushButton_Login_clicked()
{
    QString username, password;
    username = ui->lineEdit_username->text();
    password = ui->lineEdit_password->text();
    connOpen();
    QSqlQuery qry;
    if(qry.exec("SELECT username, password FROM user WHERE username=\'"+username+ "\' AND password=\'"+password+"\'"))
    {
        if(qry.next()){
            QMessageBox::information(this, "Login", "Username and password is correct");
            connClose();
            this->hide();
            halaman_admin *halamanadmin;
            halamanadmin=new halaman_admin(this);
            halamanadmin->show();
        }else{
            QMessageBox::warning(this,"Login", "Username and password is not correct");
        }
    }
}
