#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "clasedatabase.h"

ClaseDataBase::ClaseDataBase( )
{
   miDB = QSqlDatabase::addDatabase("QSQLITE");
 }

void ClaseDataBase::datosConexion(const QString &nombreBase)
{
   Nombre = nombreBase;
   miDB.setDatabaseName(nombreBase);  
}

bool ClaseDataBase::abreConexion(QString &mensaje)
{
  if (!miDB.open()){
      mensaje = miDB.lastError().text();
      return false;
  }
  Estado = "Conectado";
  return true;
}

bool ClaseDataBase::qB(const QString query, QString &mensaje)
{
    int com;
    QSqlQuery q;

    com = QString::compare(Estado, "No conectado", Qt::CaseInsensitive);
    if (com == 0){
        mensaje = "No esta conectado a ninguna base de datos.";
        return false;
    }
    if (q.exec(query)){
        mensaje = "Consulta llevada a cabo correctamente";
        return true;
    }
    mensaje = miDB.lastError().text();
    return false;
}

QString ClaseDataBase::getNombreBase()
{
    return (Nombre);
}

QString ClaseDataBase::getNombreUsuario()
{
    return (Usuario);
}

void ClaseDataBase::cerrarConexion()
{
    miDB.close();
}
