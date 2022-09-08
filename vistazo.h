#ifndef VISTAZO_H
#define VISTAZO_H

#include <QDialog>

namespace Ui {
class Vistazo;
}

class Vistazo : public QDialog
{
    Q_OBJECT

public:
    explicit Vistazo(QWidget *parent = nullptr);
    ~Vistazo();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Vistazo *ui;
};

#endif // VISTAZO_H
