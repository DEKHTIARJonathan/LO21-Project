#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include <map>
#include <QString>

#include <note/note.h>

using namespace std;

class NotesManager
{

	public:


		// Singleton
		static NotesManager&			getInstance();
		static void						destroy();

	private:
		// Member
		map<unsigned int,Note*>		m_loadedNotes;

		// Singleton
		NotesManager();	// Interdit l'instanciation directe
		NotesManager(const NotesManager& nm);	// Interdit la recopie
		NotesManager&				operator=(const NotesManager& n);	// Interdit la recopie
		static NotesManager * s_inst;	// Contient le singleton s'il est instancié

};

#endif
