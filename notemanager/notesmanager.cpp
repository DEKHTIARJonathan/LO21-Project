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

	if( it!=m_loadedNotes.end() ){
		return **it;
	}
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

void NotesManager::putToTrash(Note& n){
	// Check if Note is loaded
	QMap<unsigned int, Note*>::iterator it = m_loadedNotes.find(n.getId());

	if( it == m_loadedNotes.end() )	// Return an exception when Note 'n' wasn't referenced.
		throw NotesManagerException("Put to Trash Note ("+QString::number(n.getId())+")","Can not delete an unreferenced Note.");

	// Put Note 'n' in trash from DB.
	DatabaseManager::getInstance().putToTrash(n.getId());
}

void NotesManager::emptyTrash(const std::vector< pair <unsigned int, QString > >& trash){
	for(std::vector< pair <unsigned int, QString > >::const_iterator it = trash.begin(); it!=trash.end(); it++){
		// Check if Note is loaded
		QMap<unsigned int, Note*>::iterator f = m_loadedNotes.find(it->first);
		GeneralNoteFactory& gf = GeneralNoteFactory::getInstance();
		if( f!=m_loadedNotes.end() ){
			gf.deleteNote(*f.value());
			m_loadedNotes.erase(f);
		}
	}
	DatabaseManager::getInstance().emptyTrash();
}

void NotesManager::flush(){
	GeneralNoteFactory& gf = GeneralNoteFactory::getInstance();
	for(QMap<unsigned int, Note*>::iterator it = m_loadedNotes.begin(); it!=m_loadedNotes.end(); it++)
		gf.deleteNote(**it);
	m_loadedNotes.clear();
}

/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

NotesManager::~NotesManager(){
	flush();
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
	if( s_inst != NULL ){
		delete s_inst;
		s_inst = NULL;
	}
}
