#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include "clasedatabase.h"

#include "ingresosorteo.h"
#include "ui_ingresosorteo.h"

ingresoSorteo::ingresoSorteo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ingresoSorteo)
{
    ui->setupUi(this);

}

IngresoSorteo::~ingresoSorteo()
{
    delete ui;
}
