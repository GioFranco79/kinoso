#include <QtWidgets>
#include <iostream>
#include <QMainWindow>
#include <QStandardItemModel>
#include "ventana.h"
#include "clasedatabase.h"
#include "ingresodialog.h"
#include "vistazo.h"
#include "compara.h"
#include "combi.h"
#include "ui_ventana.h"

ventana::ventana(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ventana)
{
    ui->setupUi(this);
    QString texto;
    QSqlError erro;
    QString mensaje;
    QSqlQuery consulta;
    QStandardItemModel *model;
    int esta[25];
    int fila, colu, total, i, aux;
    ui->comboBox->addItem("Kino");
    ui->comboBox->addItem("ReKino");
    ui->comboBox->addItem("Chanchito Regalon");
    ui->comboBox->addItem("Combo Marraqueta");
    ui->comboBox->addItem("Chao Jefe 1 millon 50 años");
    ui->comboBox->addItem("Chao Jefe 2 millones 50 años");

    venBasedatos();
    consulta.prepare("SELECT * FROM sorteos WHERE tiposorteo = ?");
    consulta.addBindValue(ui->comboBox->currentText());
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
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();    
}

ventana::~ventana()
{
    delete ui;
}

void ventana::venBasedatos()
{
    QString mensaje = "";
    QString narchivo = QFileDialog::getOpenFileName(this, tr("Abrir archivo"),
                                                             "*.sqlite",
                                                             "SQLite file (*.sqlite)");
    if (!narchivo.isEmpty()){
        archivo.datosConexion(narchivo);
        if (!archivo.abreConexion(mensaje)){
            QMessageBox::critical(this, tr("Error"), mensaje);
        }
    }
    return;
}

void ventana::on_botonCambioSorteo_clicked()
{
    QString texto;
    QSqlError erro;
    QString mensaje;
    QSqlQuery consulta;
    QStandardItemModel *model;
    int esta[25];
    int fila, colu, total, i, aux;

    consulta.prepare("SELECT * FROM sorteos WHERE tiposorteo = ?");
    consulta.addBindValue(ui->comboBox->currentText());
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
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->update();
}

/************************ Función busca sorteos ganadores ***************************************/
void ventana::on_pushButton_clicked()
{
    QString texto;
    QString aux;
    QString fechamax;
    QString sorteomax;
    QSqlError erro;
    QString mensaje;
    QSqlQuery consulta;
    int puntos, gana, nganador, i, j, tpuntos, numsor, cantpuntos;
    int buscar[14];

    consulta.prepare("SELECT * FROM sorteos");
    if (!consulta.exec()){
        erro = consulta.lastError();
        mensaje = erro.text();
        QMessageBox::critical(this, tr("Error"), mensaje);
        return;
    }
    gana = 0;
    buscar[0] = ui->lE1->text().toInt();
    buscar[1] = ui->lE2->text().toInt();
    buscar[2] = ui->lE3->text().toInt();
    buscar[3] = ui->lE4->text().toInt();
    buscar[4] = ui->lE5->text().toInt();
    buscar[5] = ui->lE6->text().toInt();
    buscar[6] = ui->lE7->text().toInt();
    buscar[7] = ui->lE8->text().toInt();
    buscar[8] = ui->lE9->text().toInt();
    buscar[9] = ui->lE10->text().toInt();
    buscar[10] = ui->lE11->text().toInt();
    buscar[11] = ui->lE12->text().toInt();
    buscar[12] = ui->lE13->text().toInt();
    buscar[13] = ui->lE14->text().toInt();
    tpuntos = 0;
    numsor = 0;
    cantpuntos = 0;
    sorteomax= "Sin sorteo";
    while (consulta.next()){
          puntos = 0;
          aux = "";
          for (i=0; i<14; ++i){
              nganador = consulta.value(3+i).toInt();
              for (j=0; j<14;++j){
                 if (nganador == buscar[j]) puntos++;
              }
              if (puntos > tpuntos){
                 tpuntos = puntos;                 
                 fechamax = consulta.value(1).toString();
                 numsor = consulta.value(0).toInt();
                 sorteomax = consulta.value(2).toString();
                 cantpuntos = 1;
              }
              else{
                  if (puntos == tpuntos){
                      cantpuntos++;
                      fechamax = consulta.value(1).toString();
                      numsor = consulta.value(0).toInt();
                      sorteomax = consulta.value(2).toString();
                  }
              }
          }

          if (puntos == 14) {
              aux = consulta.value(0).toString();
              aux.append(" ["); aux.append(consulta.value(1).toString()); aux.append("] ");
              aux.append(" ["); aux.append(consulta.value(2).toString()); aux.append("] ");
              aux.append(consulta.value(3).toString()); aux.append(", ");
              aux.append(consulta.value(4).toString()); aux.append(", ");
              aux.append(consulta.value(5).toString()); aux.append(", ");
              aux.append(consulta.value(6).toString()); aux.append(", ");
              aux.append(consulta.value(7).toString()); aux.append(", ");
              aux.append(consulta.value(8).toString()); aux.append(", ");
              aux.append(consulta.value(9).toString()); aux.append(", ");
              aux.append(consulta.value(10).toString()); aux.append(", ");
              aux.append(consulta.value(11).toString()); aux.append(", ");
              aux.append(consulta.value(12).toString()); aux.append(", ");
              aux.append(consulta.value(13).toString()); aux.append(", ");
              aux.append(consulta.value(14).toString()); aux.append(", ");
              aux.append(consulta.value(15).toString()); aux.append(", ");
              aux.append(consulta.value(16).toString()); aux.append("\n");
              gana++;
          }
          texto = texto + aux;
    }
    ui->textEdit->clear();
    if (gana>0) {
       ui->textEdit->append(texto);
    }
    else {
        aux = "";
        for (i=0; i<14 ;++i){
            mensaje = QString::number(buscar[i]);
            aux.append(mensaje);
            if (i<13) aux.append(" - ");
            else aux.append("   ");
        }
        aux.append("No se encontraron coincidencias en ningun sorteo del Kino.\n");
        aux.append("\nMáxima puntuación : ");
        aux.append(QString::number(tpuntos));
        aux.append(", puntuación salió ");
        aux.append(QString::number(cantpuntos));
        aux.append(" veces, último sorteo N° [");
        aux.append(QString::number(numsor));
        aux.append("] del monto sorteado ");
        aux.append(sorteomax);
        ui->textEdit->append(aux);
    }
}

void ventana::on_pushButton_2_clicked()
{
    QString aux;
    QString apuesta;
    QSqlError erro;
    QString mensaje;
    QSqlQuery consulta;
    int **mtotal;
    int fila, total, colu, i, res, repe, coin;

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
    // **************** Reserva memoria ******************************/
    mtotal = new int *[total+1];
    for (fila=0; fila<total; fila++){
        mtotal[fila] = new int[14];
    }
    // **************** Rellena la matriz ****************************/
    consulta.first();
    fila = 0;
    do {
        for (i=3; i<17; i++){
           colu = consulta.value(i).toInt();
           mtotal[fila][i-3] = colu;
        }
        fila++;
    } while (consulta.next());
    // **************** Busca coincidencias **************************/
    ui->textEdit->clear();
    ui->textEdit->append("Apuestas ganadoras que se han repetido : ");
    coin = 0;
    for (fila=0; fila<total; fila++){
        repe = 0;
        for (i=fila+1; i<total; i++){
            res = 0;
            apuesta = "";
            for (colu=0; colu<14; colu++){
                if (mtotal[fila][colu] == mtotal[i][colu]) res++;
                apuesta.append(QString::number(mtotal[i][colu]));
                apuesta.append("  ");
            }
            apuesta.append(" ");
            if (res == 14){
                ui->textEdit->append(apuesta);
                repe++;
            }
        }
        if (repe > 0){
           aux = "Esta apuesta se repitio : " + QString::number(repe) + " veces.\n";
           ui->textEdit->append(aux);
           coin++;
        }
    }
    if (coin == 0){
       ui->textEdit->append("No hay apuestas repetidas en ");
       ui->textEdit->append(QString::number(total));
       ui->textEdit->append(" sorteos.\n");
    }

    // **************** Termina y limpia matriz **********************/
    delete mtotal;
}

void ventana::on_actionIngresar_sorteo_triggered()
{
    IngresoDialog entrando(this);
    entrando.exec();
}

void ventana::on_actionMostrar_triggered()
{
    Vistazo mostrando(this);
    mostrando.exec();
}

void ventana::on_actionCombinaciones_triggered()
{
    Combi resul(this);
    resul.exec();
}

void ventana::on_actionMigrar_base_a_texto_triggered()
{
    QSqlError erro;
    QString mensaje;
    QSqlQuery consulta;
    QFile archivo("Numeros.txt");
    QTextStream lineaArchivo(&archivo);
    int i,fila;

    consulta.prepare("SELECT * FROM sorteos");
    if (!consulta.exec()){
        erro = consulta.lastError();
        mensaje = erro.text();
        QMessageBox::critical(this, tr("Error"), mensaje);
        return;
    }
    if (archivo.open(QIODevice::WriteOnly | QIODevice::Text)){
       while (consulta.next()){
          for (i=3; i<17; i++){
              fila = consulta.value(i).toInt();
              lineaArchivo << fila << " ";
          }
          lineaArchivo << "\n";
       }
       archivo.close();
       mensaje = "Archivo de texto creado con exito";
       QMessageBox::warning( this, tr("Exito"), mensaje);
    }
}

void ventana::on_actionComparar_sorteo_triggered()
{
    Compara comparar(this);
    comparar.exec();
}

