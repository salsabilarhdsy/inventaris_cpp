#include "halaman_admin.h"
#include "ui_halaman_admin.h"

halaman_admin::halaman_admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::halaman_admin)
{
    ui->setupUi(this);
}

halaman_admin::~halaman_admin()
{
    delete ui;
}
