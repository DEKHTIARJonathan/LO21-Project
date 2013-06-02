#include "exportfactorynotfoundexception.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

// Generic ExportFactoryNotFoundException constructor
ExportFactoryNotFoundException::ExportFactoryNotFoundException( const QString & typeName ) : std::exception()
{
	m_typeName	= typeName;
}

/********************************************************************
 *                              Getter                              *
 ********************************************************************/

const QString &	ExportFactoryNotFoundException::getTypeName() const{	return m_typeName;	}

/********************************************************************
 *                          Implementation                          *
 ********************************************************************/

const char* ExportFactoryNotFoundException::what() const throw(){

	std::stringstream ss;

	ss << "The ExportFactory of type '" << m_typeName.toStdString() << "' does not exist." << std::endl;

	return ss.str().data();
}
/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

ExportFactoryNotFoundException::~ExportFactoryNotFoundException() throw(){}

