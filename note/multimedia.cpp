#include "multimedia.h"
#include "dbmanager/databasemanager.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

// Generic MultiMedia constructor
MultiMedia::MultiMedia( unsigned int id ) : Note(id), m_description(), m_path()
{
}

/********************************************************************
 *                              Getter                              *
 ********************************************************************/

const QString &	MultiMedia::getDescription() const{	return m_description;	}
const QString &	MultiMedia::getPath() const{		return m_path;			}

/********************************************************************
 *                              Setter                              *
 ********************************************************************/

void	MultiMedia::setDescription( const QString & description){	m_description	= description;
																	m_modified		= true;			}
void	MultiMedia::setPath( const QString & path){					m_path			= path;
																	m_modified		= true;			}



/********************************************************************
 *                              Method                              *
 ********************************************************************/
void	MultiMedia::binaryToWorkspace()
{

	DatabaseManager& db = DatabaseManager::getInstance();

	QFile dbFile(db.getpath());

	QFileInfo info(dbFile);

	QDir saveDir = info.absoluteDir();

	saveDir.setPath(saveDir.path()+"/binary");

	saveDir.mkpath(saveDir.path());

	if(!saveDir.exists())
		cout<<"Erreur à la création du dossier"<<endl;

	QFile from(m_path);

	QString str = from.fileName();
	QStringList parts = str.split("/");
	QString filename = parts.at(parts.size()-1);

	QFile target(saveDir.path()+"/"+filename);

	if (target.exists())
		target.remove();

	if(!from.copy(target.fileName()))
		cout<<"Erreur de copie"<<endl;
	else
	{
		m_path = target.fileName();

		db.updateNote(*this);
	}

}

