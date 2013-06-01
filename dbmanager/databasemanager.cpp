#include "DatabaseManager.h"

using namespace std;


/********************************************************************
 *                           Constructers                           *
 ********************************************************************/

DatabaseManager::DatabaseManager(QString filename, QString user, QString pass)
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
			/******** AFFICHE TOUTES LES TABLES DE LA DB *********
			 *******
			 ******
			 *****
			 ****
			 ***
			 **
			 *
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

/********************************************************************
 *                              getters                             *
 ********************************************************************/

const QString DatabaseManager::getpath() const
{
	return dbpath;
}


/********************************************************************
 *                            DB Requests                           *
 ********************************************************************/

bool DatabaseManager::query(QString query) const
{
	QSqlQuery request(*database);

	return request.exec(query);
}

bool DatabaseManager::initDB()
{
	QString qry[7];

	/*

constants::SIZE_MAX_TYPE_NOTE
constants::SIZE_MAX_TITLE
constants::SIZE_MAX_PATH
constants::SIZE_MAX_TAG

	*/

	qry[0] = "create table Note (id integer , title varchar("+QString::number(constants::SIZE_MAX_TITLE)+"), typeNote varchar("+QString::number(constants::SIZE_MAX_TYPE_NOTE)+"), primary key(id))";
	qry[1] = "create table Article (id integer, txt text, primary key(id), FOREIGN KEY(id) REFERENCES Note(id) ON DELETE CASCADE)";
	qry[2] = "create table Document (id integer, primary key(id), FOREIGN KEY(id) REFERENCES Note(id) ON DELETE CASCADE)";
	qry[3] = "create table Multimedia (id integer, description TEXT, path varchar("+QString::number(constants::SIZE_MAX_PATH)+"), primary key(id), FOREIGN KEY(id) REFERENCES Note(id) ON DELETE CASCADE)";
	qry[4] = "create table AssocDoc (docMaster integer, note integer, primary key(docMaster, note), FOREIGN KEY(docMaster) REFERENCES Document(id) ON DELETE CASCADE, FOREIGN KEY(note) REFERENCES Note(id) ON DELETE CASCADE)";
	qry[5] = "create table Tag (name varchar("+QString::number(constants::SIZE_MAX_TAG)+"), primary key(name))";
	qry[6] = "create table AssocTag (id integer, name varchar("+QString::number(constants::SIZE_MAX_TAG)+"), primary key(id, name), FOREIGN KEY(id) REFERENCES Note(id) ON DELETE CASCADE, FOREIGN KEY(name) REFERENCES Tag(name) ON DELETE CASCADE)";

	bool b = true;

	for (int i = 0; i<7; ++i)
	{
		if (!query(qry[i]))
			b &= false;
	}

	if (b)
		cout<<"DB initialisée\n\n";
	else
	{
		cout<<"Erreur ‡ l'initialisation\n\n";
		QFile::remove(dbpath);
		exit(0);
	}

	return b;
}

int DatabaseManager::getLastID() const
{
	 QSqlQuery query(*database);

	query.exec("SELECT last_insert_rowid()");

	query.next();// Only one result no need of the while loop

	return query.value(0).toInt();

}


/********************************************************************
 *                              Deleters                              *
 ********************************************************************/

bool DatabaseManager::deleteNote (unsigned int id) const
{
	return query("Delete from Note where id = "+ QString::number(id));
}

bool DatabaseManager::deleteNote () const
{
	return query("Delete from Note where 1=1");
}

/********************************************************************
 *                            Inserters                             *
 ********************************************************************/

bool DatabaseManager::insertNote (const Note& n) const
{
	QString titre = n.getTitle();
	QString type = n.metaObject()->className();

	return query("INSERT INTO Note (id, title, typeNote) VALUES (NULL, '"+titre+"','"+ type +"')");
}

int DatabaseManager::insertNote (const Article& a) const // return the idNote or -1 in case of error
{
	bool result = true;

	result &= insertNote((Note&)a);

	QString txt = a.getText();
	int id = getLastID();

	result &= query("INSERT INTO Article (id, txt) VALUES ("+ QString::number(id) +", '"+txt+"')");

	if (result)
		return id;
	else
	{
		deleteNote(id);
		return -1;
	}
}

int DatabaseManager::insertNote(const Document& d) const
{
	bool result = true;

	result &= insertNote((Note&)d);

	int id = getLastID();

	result &= query("INSERT INTO Document (id) VALUES ("+ QString::number(id) +")");

	if (result)
		return id;
	else
	{
		deleteNote(id);
		return -1;
	}
}

int DatabaseManager::insertNote(const MultiMedia &m) const
{
	bool result = true;

	result &= insertNote((Note&)m);

	QString description = m.getDescription();
	QString path = m.getPath();
	int id = getLastID();

	result &= query("INSERT INTO Multimedia (id, description, path) VALUES ("+ QString::number(id) +", '"+description+"', '"+path+"')");

	if (result)
		return id;
	else
	{
		deleteNote(id);
		return -1;
	}
}

bool DatabaseManager::insertTag (QString t) const
{
	return query("INSERT INTO Tag (name) VALUES ('"+t+"')");
}

/********************************************************************
 *                             Updaters                             *
 ********************************************************************/

bool DatabaseManager::updateNote (const Article& a)  const
{
	bool result = true;
	QString txt = a.getText();
	QString title = a.getTitle();
	int id = a.getId();

	result &= query("UPDATE Note SET title = '"+title+"' WHERE id ='"+ QString::number(id) +"'");
	result &= query("UPDATE Article SET txt = '"+txt+"' WHERE id ='"+ QString::number(id) +"'");

	return result;
}

bool DatabaseManager::updateNote (const Document& d)  const
{

	bool result = true;

	QString title = d.getTitle();
	int id = d.getId();

	result &= query("UPDATE Note SET title = '"+title+"' WHERE id ='"+ QString::number(id) +"'");

	return result;
}

bool DatabaseManager::updateNote (const MultiMedia& m)  const
{
	bool result = true;
	QString description = m.getDescription();
	QString path = m.getPath();
	QString title = m.getTitle();

	int id = m.getId();

	result &= query("UPDATE Note SET title = '"+title+"' WHERE id ='"+ QString::number(id) +"'");
	result &= query("UPDATE Multimedia SET description = '"+description+"', path = '"+path+"' WHERE id ='"+ QString::number(id) +"'");

	return result;
}


/********************************************************************
 *                            Retrievers                            *
 ********************************************************************/


void DatabaseManager::getNote(unsigned int id) const
{
	QSqlQuery request(*database);

	request.exec("Select * from Note where id = "+ QString::number(id));

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

std::vector<QString> DatabaseManager::getAllTags() const
{
	QSqlQuery request(*database);
	vector<QString> result;

	request.exec("Select * from Tag");

	while (request.next())
	{
		result.push_back(request.value(0).toString());
	}

	return result;
}

std::vector<QString> DatabaseManager::getTags(Note &n) const
{
	QSqlQuery request(*database);
	vector<QString> result;

	int id = n.getId();

	request.exec("Select name from AssocTag where id = '"+QString::number(id)+"'");

	while (request.next())
	{
		result.push_back(request.value(0).toString());
	}

	return result;
}

std::vector< pair <unsigned int, QString > > DatabaseManager::getNotes(QString tag) const
{
	std::vector< pair <unsigned int, QString > > result;
	pair <unsigned int, QString > temp;

	QSqlQuery request(*database);

	request.exec("Select a.id , title from AssocTag a, Note n where a.name = '"+tag+"' and a.id = n.id");
	while (request.next())
	{
		temp.first = request.value(0).toInt();
		temp.second = request.value(1).toString();
		result.push_back(temp);
	}

	return result;

}


/********************************************************************
 *                            Singleton                             *
 ********************************************************************/

DatabaseManager* DatabaseManager::s_inst = NULL;

DatabaseManager& DatabaseManager::getInstance(QString filename, QString user, QString pass){
	if( s_inst == NULL )
		s_inst = new DatabaseManager(filename,user,pass);
	return (*s_inst);
}

void DatabaseManager::destroy(){
	if( s_inst != NULL )
		delete s_inst;
}
