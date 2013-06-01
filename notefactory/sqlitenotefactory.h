#ifndef SQLITENOTEFACTORY_H
#define SQLITENOTEFACTORY_H

#include <map>
#include <QString>

#include <notefactory/abstractnotefactory.h>
#include <note/note.h>
#include <dbmanager/databasemanager.h>

using namespace std;

template<class TypeNote>
class SQLiteNoteFactory : public AbstractNoteFactory
{

	public:
		// Constructor
		SQLiteNoteFactory(){}

		// Implemented Method From AbstractNoteFactory
		bool constructStorage() = 0;

//		TypeNte&	buildNewNote() = 0;
//		TypeNote&	loadNote(unsigned int id) = 0;
//		TypeNote&	saveNote(const Note& n) = 0;
//		TypeNote&	deleteNote(unsigned int id) = 0;

	protected:

		//virtual void						fillSpecificPart(Note& n);

};

#endif
