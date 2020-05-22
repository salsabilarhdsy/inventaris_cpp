#include "halaman_admin.h"
#include "ui_halaman_admin.h"
#include "supplier.h"

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

void halaman_admin::on_actionSupplier_triggered()
{
    supplier *halaman_supp;
    halaman_supp=new supplier(this);
    halaman_supp->show();
}
