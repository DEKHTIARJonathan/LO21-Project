#include "notefactory.h"

map<QString,NoteFactory*> NoteFactory::s_mapNF = map<QString,NoteFactory*>();

/********************************************************************
 *                          Static Method                           *
 ********************************************************************/

void NoteFactory::initNoteFactories(){

	// Add every NoteFactory to s_mapES here ;)
}

NoteFactory&	NoteFactory::getNoteFactory(const QString& factoryName){

	map<QString,NoteFactory*>::iterator res = NoteFactory::s_mapNF.find(factoryName);

	if( res == NoteFactory::s_mapNF.end() )
		throw NoteFactoryNotFoundException(factoryName.toStdString());

	return *(res->second);
}


