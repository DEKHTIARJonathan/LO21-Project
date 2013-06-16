#include "exportfileexception.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

// Generic ExportFileException constructor
ExportFileException::ExportFileException( const QString & action, const QString & error ) : std::exception()
{
	m_action	= action;
	m_error		= error;
}

/********************************************************************
 *                              Getter                              *
 ********************************************************************/

const QString &	ExportFileException::getAction() const{	return m_action;	}
const QString &	ExportFileException::getError() const{	return m_error;		}

/********************************************************************
 *                          Implementation                          *
 ********************************************************************/

const char* ExportFileException::what() const throw(){

	std::stringstream ss;

    ss << "An error occured during '" << m_action.toStdString() << "' :" << std::endl;
	ss << "-----------Error-----------" << std::endl;
    ss << m_error.toStdString() << std::endl;
	ss << "----------------------------" << std::endl;

	return ss.str().data();
}
/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

ExportFileException::~ExportFileException() throw(){}

