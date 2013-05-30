#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QWidget>

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QString>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <iostream>


class databaseManager
{
public:
    /* *************** Constructeur ******************/
    databaseManager(QString filename = "temp");

    /***************** Getters ***********************/
    const QString getpath() const;

    /******************* Setters *********************/

    /***************** DB REQUEST ********************/
    bool query(QString query) const;
    void getPersonne(QString name = "") const;
    bool addPersonne(QString name = "", QString mob = "", QString city = "") const;
    void getInscription(QString nameUV = "") const;



 private:
    QSqlDatabase *database;
    QString dbpath;

    bool initDB();
    //QSqlTableModel *all_model;
    //QSqlTableModel *search_model;

    //void updateTable();
};

#endif // DATABASEMANAGER_H
