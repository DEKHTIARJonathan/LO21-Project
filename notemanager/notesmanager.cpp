#include "notesmanager.h"

map<QString,ExportStrategy*> NotesManager::s_mapES = map<QString,ExportStrategy*>();

/********************************************************************
 *                          Static Method                           *
 ********************************************************************/

void NotesManager::initExportStrategies(){

	NotesManager::s_mapES.insert(s_mapES.begin(), std::pair<QString,ExportStrategy*>("html",new ExportHTML()));

}

ExportStrategy&	NotesManager::getExportStrategy(const QString& strategyName){

	map<QString,ExportStrategy*>::iterator res = NotesManager::s_mapES.find(strategyName);

	if( res == NotesManager::s_mapES.end() )
		throw ExportStrategyNotFoundException(strategyName.toStdString());

	return *(res->second);
}

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

// Generic NotesManager constructor
NotesManager::NotesManager(  ) : m_loadedNotes()
{
}

/********************************************************************
 *                              Method                              *
 ********************************************************************/


/********************************************************************
 *                            Singleton                             *
 ********************************************************************/

NotesManager* NotesManager::s_inst = NULL;

NotesManager& NotesManager::getInstance(){
	if( s_inst == NULL )
		s_inst = new NotesManager();
	return (*s_inst);
}

void NotesManager::destroy(){
	if( s_inst != NULL )
		delete s_inst;
}
