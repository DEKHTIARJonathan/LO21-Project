#ifndef NOTEFACTORY_H
#define NOTEFACTORY_H

#include <map>
#include <QString>

#include <note/note.h>
#include <notefactory/notefactorynotfoundexception.h>

using namespace std;

class NoteFactory
{

	public:
		// Virtual Method
		virtual Note&						buildNewNote() = 0;
		virtual Note&						buildNoteCopy(const Note& n) = 0;
		virtual Note&						loadNote(unsigned int id) = 0;
		virtual Note&						saveNote(const Note& n) = 0;
		virtual Note&						deleteNote(unsigned int id) = 0;

		// Static Method
		static void							initNoteFactories();
		static NoteFactory&					getNoteFactory(const QString& factoryName);

		// Static Attribut
		static map<QString,NoteFactory*>	s_mapNF;

	protected:
		virtual void						fillSpecificPart(Note& n);

};

#endif
