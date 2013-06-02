#ifndef INTERFACENOTEFACTORY_H
#define INTERFACENOTEFACTORY_H

#include <note/note.h>

class InterfaceNoteFactory
{
	public:
		virtual Note&		buildNewNote() = 0;
		virtual Note&		loadNote(unsigned int id) = 0;
		virtual void		saveNote(Note& n) = 0;
		virtual void		deleteNote(Note& n) = 0;

};

#endif // INTERFACENOTEFACTORY_H
