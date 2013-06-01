#ifndef NOTEFACTORY_H
#define NOTEFACTORY_H

#include <notefactory/sqlitenotefactory.h>
#include <note/note.h>
#include <dbmanager/databasemanager.h>
#include <constants.h>
#include <QStringBuilder>

class NoteFactory : public SQLiteNoteFactory<Note>
{
	public:
		bool constructStorage();
};

#endif // NOTEFACTORY_H
