#ifndef CLASEDATABASE_H
#define CLASEDATABASE_H

#include <QtSql>

class ClaseDataBase
{
public:
    ClaseDataBase();
    bool abreConexion(QString &mensaje);
    bool qB(const QString query, QString &mensaje);
    void cerrarConexion();
    void datosConexion(const QString &nombreBase);
    QString getNombreBase();
    QString getNombreUsuario();

private:
    QSqlDatabase miDB;
    QString Nombre = "No conectado  ";
    QString Usuario = "Desconocido";
    QString Estado = "No conectado";
};

#endif // CLASEDATABASE_H
