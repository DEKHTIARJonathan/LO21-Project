#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include <QMap>
#include <QString>

#include <note/note.h>
#include <notefactory/generalnotefactory.h>

using namespace std;

class NotesManager
{

	public:
		// Method
		Note&							getNewNote(const QString &typeNote);
		Note&							getNote(unsigned int id);

		// Singleton
		static NotesManager&			getInstance();
		static void						destroy();

	private:
		// Member
		QMap<unsigned int,Note*>		m_loadedNotes;

		// Singleton
		NotesManager();	// Interdit l'instanciation directe
		NotesManager(const NotesManager& nm);	// Interdit la recopie
		NotesManager&				operator=(const NotesManager& n);	// Interdit la recopie
		static NotesManager * s_inst;	// Contient le singleton s'il est instancié

};

#endif
