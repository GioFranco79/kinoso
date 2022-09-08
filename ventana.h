#ifndef VENTANA_H
#define VENTANA_H

#include <QtGui>
#include <QMainWindow>
#include "clasedatabase.h"

namespace Ui {
class ventana;
}

class ventana : public QMainWindow
{
    Q_OBJECT

public:
    explicit ventana(QWidget *parent = nullptr);
    ~ventana();
    void venBasedatos();

private slots:
    void on_botonCambioSorteo_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_actionIngresar_sorteo_triggered();

    void on_actionMostrar_triggered();

    void on_actionCombinaciones_triggered();

    void on_actionMigrar_base_a_texto_triggered();

private:
    Ui::ventana *ui;
    ClaseDataBase archivo;
    int **matriz;
};

#endif // VENTANA_H
