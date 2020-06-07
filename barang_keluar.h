#ifndef BARANG_KELUAR_H
#define BARANG_KELUAR_H

#include <QDialog>

namespace Ui {
class barang_keluar;
}

class barang_keluar : public QDialog
{
    Q_OBJECT

public:
    explicit barang_keluar(QWidget *parent = nullptr);
    ~barang_keluar();

private:
    Ui::barang_keluar *ui;
};

#endif // BARANG_KELUAR_H
