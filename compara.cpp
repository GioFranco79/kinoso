#include <QtWidgets>
#include <iostream>
#include <QMainWindow>
#include <QStandardItemModel>
#include "compara.h"
#include "ui_compara.h"
#include "clasedatabase.h"

Compara::Compara(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Compara)
{
    ui->setupUi(this);
    QString texto;
    QSqlError erro;
    QString mensaje, sorteo;
    QSqlQuery consul;
    QSqlQuery consulta;
    QStandardItemModel *model;
    int esta[25];
    int fila, colu, total, i, aux;

    consul.prepare("SELECT * FROM sorteos ORDER BY nrosorteo DESC LIMIT 2");
    if (!consul.exec()){
        erro = consul.lastError();
        mensaje = erro.text();
        QMessageBox::critical(this, tr("Error"), mensaje);
        return;
    }
    sorteo = "800";
    while (consul.next()){
        sorteo = consul.value(0).toString();
    }

    consulta.prepare("SELECT * FROM sorteos WHERE nrosorteo = ?");
    consulta.addBindValue(sorteo);
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
    matriz = new int *[total+1];
    for (fila=0; fila<total; fila++){
        matriz[fila] = new int[25];
    }
    // **************** Rellena la matriz con ceros ******************/
    for (i=0; i<25; ++i) esta[i] = 0;
    for (fila=0; fila<total ; fila++){
        for (colu=0; colu<25; colu++){
            matriz[fila][colu] = 0;
        }
    }
    fila = 0;
    // **************** Rellena la matriz con unos *******************/
    consulta.first();
    do {
        for (i=3; i<17; i++){
           colu = consulta.value(i).toInt();
           if (colu>0 && colu<26){
               matriz[fila][colu-1] = 1;
               aux = esta[colu-1];
               aux++;
               esta[colu-1] = aux;
           }
        }
        fila++;
    } while (consulta.next());

    model = new QStandardItemModel(total+1,25);
    for (fila=0; fila<total; fila++){
        for (colu=0; colu<25; colu++){
            if (matriz[fila][colu] == 1) texto = "X";
            else texto = " ";
            //texto = QString::number(matriz[fila][colu]);

            QStandardItem* item = new QStandardItem(texto);
            if (matriz[fila][colu] == 0){
               item->setData(QVariant(QBrush(Qt::black)), Qt::BackgroundRole);
            }
            else {
               item->setData(QVariant(QBrush(Qt::red)), Qt::BackgroundRole);
            }
            item->setTextAlignment(Qt::AlignCenter);
            model->setItem(fila, colu, item);
        }
    }
    for (i=0; i<25; ++i){
        texto = QString::number(esta[i]);
        QStandardItem* item = new QStandardItem(texto);
        model->setItem(fila, i, item);
    }
    ui->TableCompara->setModel(model);
    ui->TableCompara->resizeColumnsToContents();
}

Compara::~Compara()
{
    delete ui;
}

void Compara::on_botonAceptar_clicked()
{
    close();
}

void Compara::on_botonCompara_clicked()
{
    QString texto;
    QSqlError erro;
    QString mensaje;
    QString sorteo;
    QSqlQuery consulta;
    QStandardItemModel *model;
    int esta[25];
    int fila, colu, total, i, aux;
    sorteo = ui->textSorteo->text();
    consulta.prepare("SELECT * FROM sorteos WHERE nrosorteo = ?");
    consulta.addBindValue(sorteo);
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
    delete matriz;
    matriz = new int *[total+1];
    for (fila=0; fila<total; fila++){
        matriz[fila] = new int[25];
    }
    // **************** Rellena la matriz con ceros ******************/
    for (i=0; i<25; ++i) esta[i] = 0;
    for (fila=0; fila<total ; fila++){
        for (colu=0; colu<25; colu++){
            matriz[fila][colu] = 0;
        }
    }
    fila = 0;
    // **************** Rellena la matriz con unos *******************/
    consulta.first();
    do {
        for (i=3; i<17; i++){
           colu = consulta.value(i).toInt();
           if (colu>=0 && colu<26){
               matriz[fila][colu-1] = 1;
               aux = esta[colu-1];
               aux++;
               esta[colu-1] = aux;
           }
        }
        fila++;
    } while (consulta.next());

    model = new QStandardItemModel(total+1,25);
    for (fila=0; fila<total; fila++){
        for (colu=0; colu<25; colu++){
            texto = QString::number(matriz[fila][colu]);
            QStandardItem* item = new QStandardItem(texto);
            if (matriz[fila][colu] == 0){
               item->setData(QVariant(QBrush(Qt::black)), Qt::BackgroundRole);
            }
            else {
               item->setData(QVariant(QBrush(Qt::red)), Qt::BackgroundRole);
            }
            model->setItem(fila, colu, item);
        }
    }
    for (i=0; i<25; ++i){
        texto = QString::number(esta[i]);
        QStandardItem* item = new QStandardItem(texto);
        model->setItem(fila, i, item);
    }
    ui->TableCompara->setModel(model);
    ui->TableCompara->resizeColumnsToContents();
    ui->TableCompara->update();
}

