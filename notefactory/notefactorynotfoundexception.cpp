#include "notefactorynotfoundexception.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

// Generic NoteFactoryNotFoundException constructor
NoteFactoryNotFoundException::NoteFactoryNotFoundException( const string & factoryName ) : std::exception()
{
	m_factoryName	= factoryName;
}

/********************************************************************
 *                              Getter                              *
 ********************************************************************/

const string &	NoteFactoryNotFoundException::getFactoryName() const{	return m_factoryName;	}

/********************************************************************
 *                          Implementation                          *
 ********************************************************************/

const char* NoteFactoryNotFoundException::what() const throw(){

	std::stringstream ss;

	ss << "The FactoryName '" << m_factoryName << "' does not exist." << std::endl;

	return ss.str().data();
}
/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

NoteFactoryNotFoundException::~NoteFactoryNotFoundException() throw(){}

