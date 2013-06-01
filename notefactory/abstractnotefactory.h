#ifndef ABSTRACTNOTEFACTORY_H
#define ABSTRACTNOTEFACTORY_H

#include <note/note.h>

class AbstractNoteFactory
{
	public:
		virtual bool		constructStorage() = 0;
		//virtual Note&		buildNewNote() = 0;
		//virtual Note&		loadNote(unsigned int id) = 0;
		//virtual Note&		saveNote(const Note& n) = 0;
		//virtual Note&		deleteNote(unsigned int id) = 0;
};

#endif // ABSTRACTNOTEFACTORY_H
