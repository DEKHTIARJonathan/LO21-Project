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

bool DatabaseManager::deleteTag (QString t) const
{
	return query("Delete from Tag where name ='"+t+"'");
}

bool DatabaseManager::deleteTag () const
{
	return query("Delete from Tag where 1=1");
}

/********************************************************************
 *                            Inserters                             *
 ********************************************************************/

unsigned int DatabaseManager::insertNotePrivate(const QString & type) const{
	QString titre = "";

	if (query("INSERT INTO Note (id, title, typeNote) VALUES (NULL, '"+titre+"','"+ type +"')"))
		return getLastID();
	else
		return 0;
}

bool DatabaseManager::insertMultimedia(unsigned int id) const
{
	QString description = "";
	QString path = "";

	return query("INSERT INTO Multimedia (id, description, path) VALUES ("+ QString::number(id) +", '"+description+"', '"+path+"')");
}

unsigned int DatabaseManager::insertNote(const QString& typeNote) const{
	int id = insertNotePrivate(typeNote);
	bool result = false;

	if(typeNote == "Article")
		result = query("INSERT INTO Article (id) VALUES ("+ QString::number(id) +")");
	else if(typeNote == "Document")
		result = query("INSERT INTO Document (id) VALUES ("+ QString::number(id) +")");
	else if(typeNote == "Image" ||typeNote == "Audio" || typeNote == "Video")
		result = insertMultimedia(id);

	if (result)
		return id;
	else
	{
		deleteNote(id);
		return 0;
	}
}

/*template<>
//unsigned int DatabaseManager::insertNote<Article> () const{
//	int id = insertNote("Article");

//	QString txt ="";

//	bool result = query("INSERT INTO Article (id, txt) VALUES ("+ QString::number(id) +", '"+txt+"')");

//	if (result)
//		return id;
//	else
//	{
//		deleteNote(id);
//		return 0;
//	}
//}

//template<>
//unsigned int DatabaseManager::insertNote<Audio> () const{
//	int id = insertNote("Audio");

//	if(insertMultimedia(id))
//		return id;
//	else
//	{
//		deleteNote(id);
//		return 0;
//	}
//}

//template<>
//unsigned int DatabaseManager::insertNote<Video> () const{
//	int id = insertNote("Video");

//	if(insertMultimedia(id))
//		return id;
//	else
//	{
//		deleteNote(id);
//		return 0;
//	}
//}

//template<>
//unsigned int DatabaseManager::insertNote<Image> () const{
//	int id = insertNote("Image");

//	if(insertMultimedia(id))
//		return id;
//	else
//	{
//		deleteNote(id);
//		return 0;
//	}
//}

//template<>
//unsigned int DatabaseManager::insertNote<Document> () const{
//	int id = insertNote("Document");

//	if(query("INSERT INTO Document (id) VALUES ("+ QString::number(id) +")"))
//		return id;
//	else
//	{
//		deleteNote(id);
//		return 0;
//	}
//}
*/

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

std::vector< pair <unsigned int, QString > > DatabaseManager::getNotes() const
{
	std::vector< pair <unsigned int, QString > > result;
	pair <unsigned int, QString > temp;

	QSqlQuery request(*database);

	request.exec("Select id, title from Note");

	while(request.next())
	{
		temp.first = request.value(0).toInt();
		temp.second = request.value(1).toString();

		result.push_back(temp);
	}

	return result;

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

QString DatabaseManager::getNoteType(unsigned int id)
{
	QSqlQuery request(*database);

	request.exec("Select typeNote from Note where id = '"+QString::number(id)+"'");

	request.next();

	return request.value(0).toString();
}

/********************************************************************
 *                             Fillers                              *
 ********************************************************************/


/********************************************************************
 *                   AssocBuilders // AssocRemovers                 *
 ********************************************************************/


bool DatabaseManager::addTagAssoc (Note& n, QString t) const
{
	int id = n.getId();
	return query("INSERT INTO AssocTag (id, name) VALUES ("+QString::number(id)+", '"+t+"')");
}

bool DatabaseManager::removeTagAssoc (Note& n, QString t) const
{
	int id = n.getId();
	return query("REMOVE FROM AssocTag WHERE id = "+QString::number(id)+" and name = '"+t+"'");
}

bool DatabaseManager::addNoteToDoc (Document& d, Note& n) const
{
	int idDoc = d.getId();
	int idNote = n.getId();
	if (idDoc != idNote)
		return query("INSERT INTO AssocDoc (docMaster, note) VALUES ("+QString::number(idDoc)+", "+QString::number(idNote)+")");
	else
		return false;
}

bool DatabaseManager::removeNotefromDoc (Document& d, Note& n) const
{
	int idDoc = d.getId();
	int idNote = n.getId();
	if (idDoc != idNote)
		return query("REMOVE FROM AssocDoc WHERE docMaster = "+QString::number(idDoc)+" and note = "+QString::number(idNote));
	else
		return false;
}

/********************************************************************
 *                             Fillers                              *
 ********************************************************************/

bool DatabaseManager::fillNote (Article& a)  const
{
	QSqlQuery query(*database);
	int id = a.getId();

	bool result = true;
	result &= query.exec("SELECT n.title, a.txt FROM Note n, Article a WHERE a.id = n.id = "+QString::number(id));

	query.next();// Only one result no need of the while loop

	QString title = query.value(0).toString();
	QString text = query.value(1).toString();

	a.setTitle(title);
	a.setText(text);

	return result;
}

bool DatabaseManager::fillNote (Document& d)  const
{
	QSqlQuery query(*database);
	int id = d.getId();

	bool result = true;
	result &= query.exec("SELECT title FROM Note WHERE id = "+QString::number(id));

	query.next();// Only one result no need of the while loop

	QString title = query.value(0).toString();

	d.setTitle(title);

	return result;
}

bool DatabaseManager::fillNote (MultiMedia& m)  const
{
	QSqlQuery query(*database);
	int id = m.getId();

	bool result = true;
	result &= query.exec("SELECT n.title, m.description, m.path FROM Note n, Multimedia m WHERE n.id = m.id = "+QString::number(id));

	query.next();// Only one result no need of the while loop

	QString title = query.value(0).toString();
	QString description = query.value(1).toString();
	QString path = query.value(2).toString();

	m.setTitle(title);
	m.setDescription(description);
	m.setPath(path);

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
