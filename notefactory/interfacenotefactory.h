#ifndef INTERFACENOTEFACTORY_H
#define INTERFACENOTEFACTORY_H

#include <notefactory/interfaceabstractnotefactory.h>
#include <note/note.h>

class InterfaceNoteFactory : InterfaceAbstractNoteFactory
{
	public:
		virtual Note&		buildNewNote() = 0;
		//virtual Note&		loadNote(unsigned int id) = 0;
		//virtual Note&		saveNote(const Note& n) = 0;
		//virtual Note&		deleteNote(unsigned int id) = 0;
};

#endif // INTERFACENOTEFACTORY_H
