#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include <map>
#include <QString>

#include <note/note.h>
#include <export/exporthtml.h>

using namespace std;

class NotesManager
{

	public:


		// Singleton
		static NotesManager&			getInstance();
		static void						destroy();

		// Static Method
		static void						initExportStrategies();
		static ExportStrategy&			getExportStrategy(const QString& strategyName);

		// Static Attribut
		static map<QString,ExportStrategy*>	s_mapES;
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
