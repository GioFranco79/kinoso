#include <QtWidgets>
#include <iostream>
#include <QMainWindow>
#include <QStandardItemModel>
#include "vistazo.h"
#include "ui_vistazo.h"
#include "clasedatabase.h"

Vistazo::Vistazo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Vistazo)
{
    ui->setupUi(this);

    QString texto;
    QSqlError erro;
    QString mensaje;
    QStringList lista = {"Nro Sorteo","Fecha sorteo","Tipo de sorteo","01","02","03","04","05","06","07","08","09","10","11","12","13","14"};
    QSqlQuery consulta;
    QStandardItemModel *model;
    // QList<int> anchos = {90,90,180,40,40,40,40,40,40,40,40,40,40,40,40,40,40};
    int total, row;
    total = 0;

    consulta.prepare("SELECT * FROM sorteos");
    if (!consulta.exec()){
        erro = consulta.lastError();
        mensaje = erro.text();
        QMessageBox::critical(this, tr("Error"), mensaje);
        return;
    }
    total = 0;
    while (consulta.next()){
        total++;
    }

    consulta.first();
    model = new QStandardItemModel(total,17);
    model->setHorizontalHeaderLabels(lista);
    row = 0;
    do {
       for (int column = 0; column < 17; ++column) {
            QStandardItem *item = new QStandardItem(consulta.value(column).toString());
            if (column != 2) item->setTextAlignment(Qt::AlignCenter);
            model->setItem(row, column, item);
       }
       row++;
    } while (consulta.next());
    ui->mostrar->setModel(model);
    ui->mostrar->setTextElideMode(Qt::ElideMiddle);
    ui->mostrar->setColumnWidth(0,75);
    ui->mostrar->setColumnWidth(1,90);
    ui->mostrar->setColumnWidth(2,170);
    ui->mostrar->setColumnWidth(3,25);
    ui->mostrar->setColumnWidth(4,25);
    ui->mostrar->setColumnWidth(5,25);
    ui->mostrar->setColumnWidth(6,25);
    ui->mostrar->setColumnWidth(7,25);
    ui->mostrar->setColumnWidth(8,25);
    ui->mostrar->setColumnWidth(9,25);
    ui->mostrar->setColumnWidth(10,25);
    ui->mostrar->setColumnWidth(11,25);
    ui->mostrar->setColumnWidth(12,25);
    ui->mostrar->setColumnWidth(13,25);
    ui->mostrar->setColumnWidth(14,25);
    ui->mostrar->setColumnWidth(15,25);
    ui->mostrar->setColumnWidth(16,25);
}

Vistazo::~Vistazo()
{
    delete ui;
}

void Vistazo::on_pushButton_clicked()
{
    close();
}
