#include "mainwindow.h"
#include "ui_mainwindow.h"

#define Path_to_DB "D:/inventaris/inventaris.db"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName(Path_to_DB);
    QFileInfo checkFile(Path_to_DB);

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
    if(!myDB.open()){
        qDebug() << "No Connection to Database";
        return;
    }
    QSqlQuery qry;
    if(qry.exec("SELECT username, password FROM user WHERE username=\'"+username+ "\' AND password=\'"+password+"\'"))
    {
        if(qry.next()){
            QMessageBox::information(this, "Login", "Username and password is correct");
            this->hide();
            halamanadmin=new halaman_admin(this);
            halamanadmin->show();
        }else{
            QMessageBox::warning(this,"Login", "Username and password is not correct");
        }
    }
}
