#include "notefactory.h"

using namespace constants;

/********************************************************************
 *                      Implementation Factory                      *
 ********************************************************************/

void NoteFactory::constructStorage(){
	DatabaseManager& db = DatabaseManager::getInstance();
	db.query( QString() %
		"create table Note (" %
			"id integer," %
			"typeNote varchar(" % QString::number(SIZE_MAX_TYPE_NOTE) % ")," %
			"title varchar(" % QString::number(SIZE_MAX_TITLE) % ")," %
			"primary key(id)" %
		 ")");
}
