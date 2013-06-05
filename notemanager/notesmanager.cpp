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

Note& NotesManager::getNewNote(const QString& typeNote){
	// Create new Note
	GeneralNoteFactory& gf = GeneralNoteFactory::getInstance();
	InterfaceNoteFactory& nf = gf.getFactories(typeNote);
	Note& n = nf.buildNewNote();

	// Add this new Note to instancied Note's storage
	m_loadedNotes.insert(n.getId(), &n);

	// Return new Note
	return n;
}

Note& NotesManager::getNote(unsigned int id){
	// Check if Note corresponding to 'id' is already loaded
	QMap<unsigned int, Note*>::const_iterator it = m_loadedNotes.find(id);

	if( it!=m_loadedNotes.end() )
		return **it;
	else{
		// Load Note corresponding to 'id'
		GeneralNoteFactory& gf = GeneralNoteFactory::getInstance();
		Note& n = gf.loadNote(id);

		// Add this Note to instancied Note's storage
		m_loadedNotes.insert(n.getId(), &n);

		// Return loaded Note
		return n;
	}
}

void NotesManager::saveNote(Note& n){
	// Save Note 'n'.
	GeneralNoteFactory& gf = GeneralNoteFactory::getInstance();
	gf.saveNote(n);
}

void NotesManager::deleteNote(Note& n){
	// Check if Note is loaded
	QMap<unsigned int, Note*>::iterator it = m_loadedNotes.find(n.getId());

	if( it!=m_loadedNotes.end() )	// Return an exception when Note 'n' wasn't referenced.
		throw NotesManagerException("Delete Note ("+QString::number(n.getId())+")","Can not delete an unreferenced Note.");

	// Delete Note 'n' from m_loadedNotes.
	m_loadedNotes.erase(it);

	// Delete Note 'n' from DB.
	GeneralNoteFactory& gf = GeneralNoteFactory::getInstance();
	gf.deleteNote(n);
}

void NotesManager::flush(){
	for(QMap<unsigned int, Note*>::iterator it = m_loadedNotes.begin(); it!=m_loadedNotes.end(); it++)
		delete *it;
}

NotesManager::~NotesManager(){
}

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
