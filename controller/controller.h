#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <notemanager/notesmanager.h>
#include <note/note.h>

class Controller
{

	public:
		// Constructor
		Controller( Note* actuelNote );

	private:
		// Member
		Note*	m_actuelNote;

};

#endif
