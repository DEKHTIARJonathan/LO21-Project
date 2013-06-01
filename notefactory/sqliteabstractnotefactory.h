#ifndef SQLITEABSTRACTNOTEFACTORY_H
#define SQLITEABSTRACTNOTEFACTORY_H

#include <map>
#include <QString>

#include <notefactory/interfaceabstractnotefactory.h>
#include <note/note.h>
#include <dbmanager/databasemanager.h>

using namespace std;

template<class TypeNote>
class SQLiteAbstractNoteFactory : public InterfaceAbstractNoteFactory
{

	public:
		// Constructor
		SQLiteAbstractNoteFactory( const InterfaceAbstractNoteFactory& parentFactory ){}

		// Implemented Method From InterfaceAbstractNoteFactory
		void allocPart(){

		}

	private:
		const InterfaceAbstractNoteFactory* m_parentFactory;
};

#endif // SQLITEABSTRACTNOTEFACTORY_H
