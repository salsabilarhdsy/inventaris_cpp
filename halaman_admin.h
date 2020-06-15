#ifndef HALAMAN_ADMIN_H
#define HALAMAN_ADMIN_H

#include <QMainWindow>

namespace Ui {
class halaman_admin;
}

class halaman_admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit halaman_admin(QWidget *parent = nullptr);
    ~halaman_admin();

private slots:
    void on_actionSupplier_triggered();

    void on_actionBarang_Masuk_triggered();

    void on_actionStok_Barang_triggered();

    void on_actionPeminjaman_Barang_triggered();

    void on_actionBarang_Keluar_triggered();

    void on_actionBarang_triggered();

    void on_actionKeluar_triggered();

private:
    Ui::halaman_admin *ui;

};

#endif // HALAMAN_ADMIN_H
