#ifndef INGRESOSORTEO_H
#define INGRESOSORTEO_H

#include <QDialog>

namespace Ui {
class ingresoSorteo;
}

class ingresoSorteo : public QDialog
{
    Q_OBJECT

public:
    explicit ingresoSorteo(QWidget *parent = nullptr);
    ~ingresoSorteo();

private slots:


private:
    Ui::ingresoSorteo *ui;

};

#endif // INGRESOSORTEO_H
