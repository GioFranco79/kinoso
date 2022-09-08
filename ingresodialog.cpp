#include <QtWidgets>
#include <iostream>
#include <QMainWindow>
#include <QStandardItemModel>
#include "clasedatabase.h"
#include "ingresodialog.h"
#include "ui_ingresodialog.h"

#define NJ 14
#define NS 6

IngresoDialog::IngresoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IngresoDialog)
{
    ui->setupUi(this);
    QDate fecha;

    ui->comboBox->addItem("Kino");
    ui->comboBox->addItem("ReKino");
    ui->comboBox->addItem("Chanchito Regalon");
    ui->comboBox->addItem("Combo Marraqueta");
    ui->comboBox->addItem("Chao Jefe 1 millon 50 años");
    ui->comboBox->addItem("Chao Jefe 2 millones 50 años");
    ui->dateEdit->setDate(fecha.currentDate());
}

IngresoDialog::~IngresoDialog()
{
    delete ui;
}

void IngresoDialog::on_pushButton_2_clicked()
{
    close();
}

void IngresoDialog::on_pushButton_clicked()
{
    QSqlError erro;
    QString mensaje;
    QString auxStr;
    QString llena;
    QString ventamen;
    QSqlQuery consulta;
    int pasa,aux,i,j,indm, sorteo;
    int nume[14];

    sorteo = ui->lsorteo->text().toInt();
    nume[0] = ui->lN01->text().toInt();
    nume[1] = ui->lN02->text().toInt();
    nume[2] = ui->lN03->text().toInt();
    nume[3] = ui->lN04->text().toInt();
    nume[4] = ui->lN05->text().toInt();
    nume[5] = ui->lN06->text().toInt();
    nume[6] = ui->lN07->text().toInt();
    nume[7] = ui->lN08->text().toInt();
    nume[8] = ui->lN09->text().toInt();
    nume[9] = ui->lN10->text().toInt();
    nume[10] = ui->lN11->text().toInt();
    nume[11] = ui->lN12->text().toInt();
    nume[12] = ui->lN13->text().toInt();
    nume[13] = ui->lN14->text().toInt();

   /********************************* ordena de menor a mayor los numeros ingresados ****************************************/
    for (i=0; i<NJ-1; ++i){
        indm = i;
        for (j=i+1;j<NJ;++j) {
            if (nume[j] < nume[indm]){
                indm = j;
            }
        }
        aux=nume[indm];
        nume[indm] = nume[i];
        nume[i] = aux;
    }
    /******************************** Verifica que los numeros esten en rango **********************************************/
    pasa = 0;
    for (i=0;i<NJ;i++) {
        if (nume[i]>0 && nume[i]<26){
           pasa++;
        }
    }
    /******************************** Verifica que los numeros no esten repetidos ******************************************/
    for (i=0; i<NJ-1; ++i){
        for (j=i+1;j<NJ;++j) {
            if (nume[j] == nume[i]){
                pasa = 0;
            }
        }
    }

    if (pasa == 14 && sorteo > 0){
    /********************************* Graba el sorteo en la base de datos *************************************************/
       consulta.prepare("INSERT INTO sorteos (nrosorteo, fecha, tiposorteo, "
                     "n01, n02, n03, n04, n05, n06, n07, n08, n09, n10, n11, n12, n13, n14) VALUES "
                     "(:nr, :fe, :ts, :N01, :N02, :N03, :N04, :N05, :N06, :N07, :N08, :N09, :N10, :N11, :N12, :N13, :N14)");
       consulta.bindValue(":nr", ui->lsorteo->text());
       consulta.bindValue(":fe", ui->dateEdit->date());
       consulta.bindValue(":ts", ui->comboBox->currentText());
       consulta.bindValue(":N01", nume[0]);
       consulta.bindValue(":N02", nume[1]);
       consulta.bindValue(":N03", nume[2]);
       consulta.bindValue(":N04", nume[3]);
       consulta.bindValue(":N05", nume[4]);
       consulta.bindValue(":N06", nume[5]);
       consulta.bindValue(":N07", nume[6]);
       consulta.bindValue(":N08", nume[7]);
       consulta.bindValue(":N09", nume[8]);
       consulta.bindValue(":N10", nume[9]);
       consulta.bindValue(":N11", nume[10]);
       consulta.bindValue(":N12", nume[11]);
       consulta.bindValue(":N13", nume[12]);
       consulta.bindValue(":N14", nume[13]);
       if (!consulta.exec()){
           erro = consulta.lastError();
           mensaje = erro.text();
           QMessageBox::critical(this, tr("Error"), mensaje);
           return;
       }
       QMessageBox::StandardButton resp;
       llena = "";
       i=0;
       while (i<NJ){
           auxStr = llena + QString::number(nume[i]);
           ++i;
           if (i<NJ){
               llena = auxStr + "-";
           }
       }
       llena = "Numeros guardados : " + auxStr + "\n\n¿Desea ingresar otro sorteo?";
       ventamen = "Sorteo nro " + QString::number(sorteo) + " guardado con exito";
       resp = QMessageBox::question(this, ventamen, llena, QMessageBox::Yes|QMessageBox::No);
       if (resp == QMessageBox::Yes) {
           ui->lN01->setText("");
           ui->lN02->setText("");
           ui->lN03->setText("");
           ui->lN04->setText("");
           ui->lN05->setText("");
           ui->lN06->setText("");
           ui->lN07->setText("");
           ui->lN08->setText("");
           ui->lN09->setText("");
           ui->lN10->setText("");
           ui->lN11->setText("");
           ui->lN12->setText("");
           ui->lN13->setText("");
           ui->lN14->setText("");
           auxStr = ui->comboBox->currentText();
           i = ui->comboBox->findText(auxStr);
           i++;
           if (i >= NS){
               sorteo++;
               auxStr = QString::number(sorteo);
               ui->lsorteo->setText("");
               ui->lsorteo->setText(auxStr);
               ui->comboBox->setCurrentIndex(0);
               ui->dateEdit->setFocus();                         
           }
           else {
               ui->comboBox->setCurrentIndex(i);
               ui->lsorteo->setFocus();
           }
         } else {
           close();
         }
    }
    else {
        if (sorteo < 1){
           QMessageBox::critical(this, tr("Error"), tr("Ingrese un número de sorteo valido."));
        }
        else {
           QMessageBox::critical(this, tr("Error"), tr("Los números no pueden ser menores a 1 ni mayores a 25,\nni tampoco puede haber números repetidos."));
        }
        return;
    }
}
