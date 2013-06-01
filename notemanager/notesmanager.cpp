#include "notesmanager.h"

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
