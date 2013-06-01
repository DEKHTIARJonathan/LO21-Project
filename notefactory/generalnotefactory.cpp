#include "generalnotefactory.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

GeneralNoteFactory::GeneralNoteFactory(  ) : m_noteFactories()
{
}

/********************************************************************
 *                              Method                              *
 ********************************************************************/

bool GeneralNoteFactory::constructDB(){
	DatabaseManager& db = DatabaseManager::getInstance();
	return true;
}

/********************************************************************
 *                            Singleton                             *
 ********************************************************************/

GeneralNoteFactory* GeneralNoteFactory::s_inst = NULL;

GeneralNoteFactory& GeneralNoteFactory::getInstance(){
	if( s_inst == NULL )
		s_inst = new GeneralNoteFactory();
	return (*s_inst);
}

void GeneralNoteFactory::destroy(){
	if( s_inst != NULL )
		delete s_inst;
}
