#include "exportstrategynotfoundexception.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

// Generic ExportStrategyNotFoundException constructor
ExportStrategyNotFoundException::ExportStrategyNotFoundException( const QString & esName ) : std::exception()
{
	m_esName	= esName;
}

/********************************************************************
 *                              Getter                              *
 ********************************************************************/

const  QString&	ExportStrategyNotFoundException::getEsName() const{	return m_esName;	}

/********************************************************************
 *                          Implementation                          *
 ********************************************************************/

const char* ExportStrategyNotFoundException::what() const throw(){

	std::stringstream ss;

	ss << "The ExportStrategy '" << m_esName.toStdString() << "' does not exist." << std::endl;

	return ss.str().data();
}
/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

ExportStrategyNotFoundException::~ExportStrategyNotFoundException() throw(){}

