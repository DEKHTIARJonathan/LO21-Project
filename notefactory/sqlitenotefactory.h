#ifndef SQLITENOTEFACTORY_H
#define SQLITENOTEFACTORY_H

#include <map>
#include <QString>

#include <notefactory/interfaceabstractnotefactory.h>
#include <notefactory/interfacenotefactory.h>
#include <note/note.h>
#include <dbmanager/databasemanager.h>

using namespace std;

template<class TypeNote>
class SQLiteNoteFactory : public InterfaceNoteFactory
{

	public:
		// Constructor
		SQLiteNoteFactory(){}

		// Implemented Method From InterfaceNoteFactory
		TypeNote& buildNewNote(){
			unsigned int newId = allocPart();
			return *(new TypeNote(newId));
		}

		TypeNote&	loadNote(unsigned int id) = 0;
//		TypeNote&	saveNote(const Note& n) = 0;
//		TypeNote&	deleteNote(unsigned int id) = 0;

};

#endif
