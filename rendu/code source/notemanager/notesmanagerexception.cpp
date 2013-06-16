#include "notesmanagerexception.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

// Generic NotesManagerException constructor
NotesManagerException::NotesManagerException( const QString & action, const QString & errorMsg ) : std::exception()
{
	m_action	= action;
	m_errorMsg	= errorMsg;
}

/********************************************************************
 *                              Getter                              *
 ********************************************************************/

const QString &	NotesManagerException::getAction() const{	return m_action;	}
const QString &	NotesManagerException::getErrorMsg() const{	return m_errorMsg;	}

/********************************************************************
 *                          Implementation                          *
 ********************************************************************/

const char* NotesManagerException::what() const throw(){

	std::stringstream ss;

	ss << "An error occured during '" << m_action.toStdString() << "' process :" << std::endl;
	ss << "-----------Error----------" << std::endl;
	ss << m_errorMsg.toStdString() << std::endl;
	ss << "---------------------------" << std::endl;

	return ss.str().data();
}
/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

NotesManagerException::~NotesManagerException() throw(){}

