#include "DatabaseManager.h"

using namespace std;

DatabaseManager::DatabaseManager(QString filename, QString user, QString pass)
{
    database = new QSqlDatabase();

    //set database driver to QSQLITE
    *database = QSqlDatabase::addDatabase("QSQLITE");

    dbpath = QDir::currentPath() +"/"+ filename + ".lo21";

	QFile file(dbpath);
	if(file.exists())
		file.remove();
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
		if (dbIsNew){
			cout << "Creating Database.." << endl;
            initDB();
		}
        else
        {
			/*
			QStringList list = database->tables(QSql::Tables);
            QStringList::Iterator it = list.begin();
            while( it != list.end() )
            {
                cout << "Table: " << it->toStdString() << "\n";
                ++it;
			}
			*/
        }
        database->exec("PRAGMA foreign_keys=ON;");
    }

}

const QString DatabaseManager::getpath() const
{
    return "Path " + dbpath+"\n";
}

bool DatabaseManager::query(QString query) const
{
    QSqlQuery request(*database);

    return request.exec(query);
}

void DatabaseManager::getNote(unsigned int id) const
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

void DatabaseManager::getNote() const
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

bool DatabaseManager::insertNote(QString titre, QString type) const
{
    return query("INSERT INTO Note (idNote, titre, typeNote) VALUES (NULL, '"+titre+"','"+ type +"')");
}

bool DatabaseManager::initDB()
{
//	QString qry[8];

//    qry[0] = "create table TypeNote (name varchar(30), primary key(name))";
//    qry[1] = "create table Note (idNote integer , titre varchar(255), typeNote varchar(30), primary key(idNote), FOREIGN KEY(typeNote) REFERENCES TypeNote(name) ON DELETE CASCADE)";
//    qry[2] = "create table Article (idArticle integer, primary key(idArticle), FOREIGN KEY(idArticle) REFERENCES Note(idNote) ON DELETE CASCADE)";
//    qry[3] = "create table Document (idDoc integer, primary key(idDoc), FOREIGN KEY(idDoc) REFERENCES Note(idNote) ON DELETE CASCADE)";
//    qry[4] = "create table Binary (idBin integer, primary key(idBin), FOREIGN KEY(idBin) REFERENCES Note(idNote) ON DELETE CASCADE)";
//    qry[5] = "create table AssocDoc (docMaster integer, docSlave integer, primary key(docMaster, docSlave), FOREIGN KEY(docMaster) REFERENCES Document(idDoc) ON DELETE CASCADE, FOREIGN KEY(docSlave) REFERENCES Note(idNote) ON DELETE CASCADE)";
//	qry[6] = "create table Tag (name varchar(30), primary key(name))";
//	qry[7] = "create table AssocTag (idNote integer, name varchar(30), primary key(idNote, name), FOREIGN KEY(idNote) REFERENCES Note(idNote) ON DELETE CASCADE, FOREIGN KEY(name) REFERENCES Tag(name) ON DELETE CASCADE)";

//    bool b = true;

//	for (int i = 0; i<8; ++i)
//    {
//        if (!query(qry[i]))
//            b = false;
//    }

//    b += addType();

//    if (b)
//        cout<<"DB initialisée\n\n";
//    else
//    {
//        cout<<"Erreur �  l'initialisation\n\n";
//        exit(0);
//    }
	return true;
}

bool DatabaseManager::addType(QString type) const
{
    return query("INSERT INTO TypeNote (name) VALUES ('"+ type +"')");
}

bool DatabaseManager::addType() const
{
    bool b = true;

    b += addType("Article");
    b += addType("Document");
    b += addType("Audio");
    b += addType("Image");
    b += addType("Video");

    return b;
}

bool DatabaseManager::deleteNote (unsigned int id) const
{
    return query("Delete from Note where idNote = "+ QString::number(id));
}

bool DatabaseManager::deleteNote () const
{
    return query("Delete from Note where 1=1");
}

void DatabaseManager::printTable() const{
	QStringList list = database->tables(QSql::Tables);
	QStringList::Iterator it = list.begin();
	cout << "------- Tables --------" << endl;
	while( it != list.end() )
	{
		cout << "Table: " << it->toStdString() << endl;
		++it;
	}
	cout << "-----------------------" << endl;
}

/********************************************************************
 *                            Singleton                             *
 ********************************************************************/

DatabaseManager* DatabaseManager::s_inst = NULL;

DatabaseManager& DatabaseManager::getInstance(){
	if( s_inst == NULL )
		s_inst = new DatabaseManager();
	return (*s_inst);
}

void DatabaseManager::destroy(){
	if( s_inst != NULL )
		delete s_inst;
}
