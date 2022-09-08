#ifndef INGRESODIALOG_H
#define INGRESODIALOG_H

#include <QDialog>

namespace Ui {
class IngresoDialog;
}

class IngresoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IngresoDialog(QWidget *parent = nullptr);
    ~IngresoDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::IngresoDialog *ui;
};

#endif // INGRESODIALOG_H
