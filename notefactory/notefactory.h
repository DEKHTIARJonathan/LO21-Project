#ifndef NOTEFACTORY_H
#define NOTEFACTORY_H

#include <notefactory/interfacenotefactory.h>
#include <dbmanager/databasemanager.h>

template<class NoteType>
class NoteFactory : public InterfaceNoteFactory
{
	public:
		Note& buildNewNote(){
			DatabaseManager& db = DatabaseManager::getInstance();

			unsigned int id = db.insertNote(NoteType::staticMetaObject.className());
			NoteType& n = *(new NoteType(id));

			return n;
		}

		Note& loadNote(unsigned int id){
			DatabaseManager& db = DatabaseManager::getInstance();

			NoteType& n = *(new NoteType(id));
			db.fillNote( n );

			return n;
		}

		void saveNote(Note &n){
			DatabaseManager& db = DatabaseManager::getInstance();

			NoteType& casted_n = (NoteType&) n;
			db.updateNote(casted_n);
		}

};

#endif // NOTEFACTORY_H
