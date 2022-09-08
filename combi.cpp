#include "combi.h"
#include "ui_combi.h"
#include <QtWidgets>
#include <QMainWindow>

#define UNIVERSO 25
#define infinito for(;;)

Combi::Combi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Combi)
{
    ui->setupUi(this);
}

Combi::~Combi()
{
    delete ui;
}

void Combi::on_botonSalir_clicked()
{
    close();
}

void Combi::on_botonCombi_clicked()
{
    int* comb;
    int m, n, r;
    long int num;
    int i, j, nuevo_valor;
    QString mensaje;
    QString aux;

    m = ui->numLine->text().toInt();
    n = UNIVERSO;

    if (m > 14 || m < 3){
       mensaje = "El número no puede ser menor a 3\nni mayor a 14.";
       QMessageBox::critical(this, tr("Error"), mensaje);
       ui->numLine->setFocus();
    }
    comb = new int[m];
    if (comb == nullptr){
       mensaje = "No queda memoria para\nel arreglo de combinaciones.";
       QMessageBox::critical(this, tr("Error"), mensaje);
       return;
    }
    num = 1;
    for(i = 0; i < m; ++i) comb[i] = i + 1;
    mensaje = "";
    infinito {
       r = buscarCombi(comb, m);
       aux = "";
       if (r > 3){
           for (j=0; j < m; ++j){
               aux.append(QString::number(comb[j])); aux.append(" ");
           }
           aux.append(" Combinacion Nro: "); aux.append(QString::number(num));
           aux.append(" Repetida "); aux.append(QString::number(r));
           aux.append(" veces. \n");
       }
       ui->textoB->clear();
       ui->textoB->append(aux);
       ui->textoB->update();
       num = num + 1;
       for (i=m-1; i>-1 && comb[i]==n-((m-1)-i);--i)
          ;
       if (i == -1) return;
       nuevo_valor = ++comb[i];
       while (i < m)
          comb[++i] = ++nuevo_valor;
    }
 }

int Combi::buscarCombi(int* combina, int tot){
   QFile entrada("Numeros.txt");
   QString line;
   QString nomArch;
   QTextStream in(&entrada);
   QStringList lista;
   int i, j, sum, repe=0;
   nomArch = "Resultado_" + QString::number(tot) + ".txt";
   QFile salida(nomArch);
   QTextStream out(&salida);

   if (entrada.open(QIODevice::ReadOnly)){
       if (salida.open(QIODevice::Append | QIODevice::Text)){
          while (!in.atEnd()){
            sum = 0;
            line = in.readLine();
            lista = line.split(' ');
            for (i = 0; i<tot; ++i){
                for (j=i; j<tot; ++j){
                    if (combina[i]==lista[j].toInt()){
                        ++sum;
                    }
                }
            }
            if (sum == tot) ++repe;
          }
          if (repe > 2){
             for (i=0; i<tot; ++i){
                  out << combina[i] << " - ";
             }
             out << " / Combinacion Repetida " << repe << " veces. \n";
          }
          salida.close();
       }
       entrada.close();
       return repe;
   }
   return -1;
}
