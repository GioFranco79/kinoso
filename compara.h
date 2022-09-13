#ifndef COMPARA_H
#define COMPARA_H

#include <QDialog>

namespace Ui {
class Compara;
}

class Compara : public QDialog
{
    Q_OBJECT

public:
    explicit Compara(QWidget *parent = nullptr);
    ~Compara();

private slots:   
    void on_botonAceptar_clicked();
    void on_botonCompara_clicked();

private:
    int **matriz;
    Ui::Compara *ui;
};

#endif // COMPARA_H
