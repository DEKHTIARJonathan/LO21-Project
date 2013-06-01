#ifndef NOTEFACTORY_H
#define NOTEFACTORY_H

#include <notefactory/interfaceabstractnotefactory.h>
#include <note/note.h>
#include <dbmanager/databasemanager.h>
#include <constants.h>
#include <QStringBuilder>

class NoteFactory// : public SQLiteNoteFactory<Note>
{
	public:
		void constructStorage();
};

#endif // NOTEFACTORY_H
