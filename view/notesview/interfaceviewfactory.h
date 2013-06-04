#ifndef INTERFACEVIEWFACTORY_H
#define INTERFACEVIEWFACTORY_H

#include <note/note.h>
#include <view/notesview/noteview.h>

class InterfaceViewFactory
{
	public:
		virtual NoteView&	buildNoteView(Note& n) = 0;
};

#endif // INTERFACEVIEWFACTORY_H
