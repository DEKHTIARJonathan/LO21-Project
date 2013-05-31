#include "databasemanager.h"

using namespace std;

databaseManager::databaseManager(QString filename, QString user, QString pass)
{
    database = new QSqlDatabase();

    //set database driver to QSQLITE
    *database = QSqlDatabase::addDatabase("QSQLITE");

    dbpath = QDir::currentPath() +"/"+ filename + ".lo21";

    QFile file(dbpath);
    bool dbIsNew = !file.exists();

    database->setDatabaseName(dbpath);

    //can be removed
    database->setHostName("localhost");
    database->setUserName(user);
    database->setPassword(pass);

    if(!database->open())
    {
        std::cout<<"Erreur, Impossible d'ouvrir la base de données.";
    }
    else
    {
        if (dbIsNew)
            initDB();
        else
        {
            /*QStringList list = database->tables(QSql::Tables);
            QStringList::Iterator it = list.begin();
            while( it != list.end() )
            {
                cout << "Table: " << it->toStdString() << "\n";
                ++it;
            }*/
        }
        database->exec("PRAGMA foreign_keys=ON;");
    }

}

const QString databaseManager::getpath() const
{
    return "Path " + dbpath+"\n";
}

bool databaseManager::query(QString query) const
{
    QSqlQuery request(*database);

    return request.exec(query);
}

void databaseManager::getNote(unsigned int id) const
{
    QSqlQuery request(*database);

    request.exec("Select * from Note where idNote = "+ QString::number(id));

    while(request.next())
    {
        QString idNote = request.value(0).toString();
        QString titre = request.value(1).toString();
        QString type = request.value(2).toString();

        cout<<"idNote : " << idNote.toStdString() << " || titre : " << titre.toStdString() << " || type : " << type.toStdString() <<endl;
    }

}

void databaseManager::getNote() const
{
    QSqlQuery request(*database);

    request.exec("Select * from Note");

    while(request.next())
    {
        QString idNote = request.value(0).toString();
        QString titre = request.value(1).toString();
        QString type = request.value(2).toString();

        cout<<"idNote : " << idNote.toStdString() << " || titre : " << titre.toStdString() << " || type : " << type.toStdString() <<endl;
    }

}

bool databaseManager::insertNote(QString titre, QString type) const
{
    return query("INSERT INTO Note (idNote, titre, typeNote) VALUES (NULL, '"+titre+"','"+ type +"')");
}

bool databaseManager::initDB()
{
    QString qry[6];

    qry[0] = "create table TypeNote (name varchar(30), primary key(name))";
    qry[1] = "create table Note (idNote integer , titre varchar(255), typeNote varchar(30), primary key(idNote), FOREIGN KEY(typeNote) REFERENCES TypeNote(name) ON DELETE CASCADE)";
    qry[2] = "create table Article (idArticle integer, primary key(idArticle), FOREIGN KEY(idArticle) REFERENCES Note(idNote) ON DELETE CASCADE)";
    qry[3] = "create table Document (idDoc integer, primary key(idDoc), FOREIGN KEY(idDoc) REFERENCES Note(idNote) ON DELETE CASCADE)";
    qry[4] = "create table Binary (idBin integer, primary key(idBin), FOREIGN KEY(idBin) REFERENCES Note(idNote) ON DELETE CASCADE)";
    qry[5] = "create table AssocDoc (docMaster integer, docSlave integer, primary key(docMaster, docSlave), FOREIGN KEY(docMaster) REFERENCES Document(idDoc) ON DELETE CASCADE, FOREIGN KEY(docSlave) REFERENCES Note(idNote) ON DELETE CASCADE)";

    bool b = true;

    for (int i = 0; i<6; ++i)
    {
        if (!query(qry[i]))
            b = false;
    }

    b += addType();

    if (b)
        cout<<"DB initialisée\n\n";
    else
    {
        cout<<"Erreur à l'initialisation\n\n";
        exit(0);
    }

    return b;
}

bool databaseManager::addType(QString type) const
{
    return query("INSERT INTO TypeNote (name) VALUES ('"+ type +"')");
}

bool databaseManager::addType() const
{
    bool b = true;

    b += addType("Article");
    b += addType("Document");
    b += addType("Audio");
    b += addType("Image");
    b += addType("Video");

    return b;
}

bool databaseManager::deleteNote (unsigned int id) const
{
    return query("Delete from Note where idNote = "+ QString::number(id));
}

bool databaseManager::deleteNote () const
{
    return query("Delete from Note where 1=1");
}
