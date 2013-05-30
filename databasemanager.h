#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QWidget>

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QString>
#include <QCoreApplication>
#include <QDir>
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


 private:
    QSqlDatabase *database;
    QString dbpath;
    //QSqlTableModel *all_model;
    //QSqlTableModel *search_model;

    //void updateTable();
};

#endif // DATABASEMANAGER_H
