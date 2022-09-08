#ifndef COMBI_H
#define COMBI_H

#include <QDialog>

namespace Ui {
class Combi;
}

class Combi : public QDialog
{
    Q_OBJECT

public:
    explicit Combi(QWidget *parent = nullptr);
    ~Combi();

private slots:
    void on_botonSalir_clicked();
    void on_botonCombi_clicked();
    int buscarCombi(int* combina, int tot);

private:
    Ui::Combi *ui;
};

#endif // COMBI_H
