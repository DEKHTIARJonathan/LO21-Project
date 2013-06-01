#ifndef INTERFACENOTEFACTORY_H
#define INTERFACENOTEFACTORY_H

#include <note/note.h>

class InterfaceNoteFactory
{
	public:
		virtual Note&		buildNewNote();
		virtual Note&		loadNote(unsigned int id);
		virtual void		deleteNote(Note& n);

};

#endif // INTERFACENOTEFACTORY_H
