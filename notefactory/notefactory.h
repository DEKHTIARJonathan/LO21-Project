#ifndef NOTEFACTORY_H
#define NOTEFACTORY_H

#include <notefactory/interfacenotefactory.h>
#include <dbmanager/databasemanager.h>

template<class noteType>
class NoteFactory : public InterfaceNoteFactory
{
	public:
		Note& buildNewNote(){
			DatabaseManager& db = DatabaseManager::getInstance();

			//db.insertNote()
		}

		Note& loadNote(unsigned int id){
			DatabaseManager& db = DatabaseManager::getInstance();

			db.fillNote( *(new noteType(id)) );
		}

};

#endif // NOTEFACTORY_H
