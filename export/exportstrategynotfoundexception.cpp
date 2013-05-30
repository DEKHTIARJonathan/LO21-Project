#include "exportstrategynotfoundexception.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

// Generic ExportStrategyNotFoundException constructor
ExportStrategyNotFoundException::ExportStrategyNotFoundException( const std::string & esName ) : std::exception()
{
	m_esName	= esName;
}

/********************************************************************
 *                              Getter                              *
 ********************************************************************/

const std::string &	ExportStrategyNotFoundException::getEsName() const{	return m_esName;	}

/********************************************************************
 *                          Implementation                          *
 ********************************************************************/

const char* ExportStrategyNotFoundException::what() const throw(){

	std::stringstream ss;

	ss << "The ExportStrategy '" << m_esName << "' does not exist." << std::endl;

	return ss.str().data();
}
/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

ExportStrategyNotFoundException::~ExportStrategyNotFoundException() throw(){}

