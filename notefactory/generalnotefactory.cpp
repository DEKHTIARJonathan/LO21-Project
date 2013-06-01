#include "generalnotefactory.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

GeneralNoteFactory::GeneralNoteFactory(  )
{
}

/********************************************************************
 *                              Method                              *
 ********************************************************************/



/********************************************************************
 *                            Singleton                             *
 ********************************************************************/

GeneralNoteFactory* GeneralNoteFactory::s_inst = NULL;

GeneralNoteFactory& GeneralNoteFactory::getInstance(){
	if( s_inst == NULL )
		s_inst = new GeneralNoteFactory();
	return (*s_inst);
}

void GeneralNoteFactory::destroy(){
	if( s_inst != NULL )
		delete s_inst;
}
