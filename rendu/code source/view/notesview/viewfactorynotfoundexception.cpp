#include "viewfactorynotfoundexception.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

// Generic ViewFactoryNotFoundException constructor
ViewFactoryNotFoundException::ViewFactoryNotFoundException( const QString & typeName ) : std::exception()
{
	m_typeName	= typeName;
}

/********************************************************************
 *                              Getter                              *
 ********************************************************************/

const QString &	ViewFactoryNotFoundException::getTypeName() const{	return m_typeName;	}

/********************************************************************
 *                          Implementation                          *
 ********************************************************************/

const char* ViewFactoryNotFoundException::what() const throw(){

	std::stringstream ss;

	ss << "The ViewFactory for type '" << m_typeName.toStdString() << "' does not exist." << std::endl;

	return ss.str().data();
}
/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

ViewFactoryNotFoundException::~ViewFactoryNotFoundException() throw(){}

