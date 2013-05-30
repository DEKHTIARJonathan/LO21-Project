#include "databasemanager.h"

using namespace std;

databaseManager::databaseManager(QString filename)
{
    database = new QSqlDatabase();

    //set database driver to QSQLITE
    *database = QSqlDatabase::addDatabase("QSQLITE");

    dbpath = QDir::currentPath() +"/"+ filename + ".lo21";

    database->setDatabaseName(dbpath);

    //can be removed
    database->setHostName("localhost");
    database->setUserName("");
    database->setPassword("");

    if(!database->open())
    {
        std::cout<<"Erreur, Impossible d'ouvrir la base de données.";
    }
    else
    {
        QSqlQuery query;
        /*query.exec("create table Contacts "
                          "(Name varchar(20), "
                          "Mobile varchar(20), "
                          "City varchar(30), "
                         "primary key(Name, Mobile))");
        //query.exec("insert into Contacts (Name,Mobile,City) Values ('John','0561390189', 'Toulouse')");*/
    }

    /*all_model = new QSqlTableModel(this, *database);
    updateTable();

    search_model = new QSqlTableModel(this, *database);
    search_model->setTable("Contacts");*/
}

const QString databaseManager::getpath() const
{
    return dbpath;
}

bool databaseManager::query(QString query) const
{
    QSqlQuery request;

    return request.exec(query);
}

void databaseManager::getPersonne(QString name) const
{
    QSqlQuery request;
    QString query;
    if (name == "")
        query = "Select * from Contacts";
    else
        query = "Select * from Contacts where Name = "+name;

    request.exec(query);

    while(request.next())
    {
        QString Name = request.value(0).toString();
        QString Mobile = request.value(1).toString();
        QString City = request.value(2).toString();

        cout<<"Nom :" << Name.toStdString() << " || Num :" << Mobile.toStdString() << " || City :"<< City.toStdString()<<endl;
    }

}

