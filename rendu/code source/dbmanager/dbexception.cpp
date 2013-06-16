#include "dbexception.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

// Generic DBException constructor
DBException::DBException( const QString & procedure, const QString & msgError ) : std::exception()
{
	m_procedure	= procedure;
	m_msgError	= msgError;
}

/********************************************************************
 *                              Getter                              *
 ********************************************************************/

const QString &	DBException::getProcedure() const{	return m_procedure;	}
const QString &	DBException::getMsgError() const{	return m_msgError;	}

/********************************************************************
 *                          Implementation                          *
 ********************************************************************/

const char* DBException::what() const throw(){

	std::stringstream ss;

	ss << "An error occured on '" << m_procedure.toStdString() << "' procedure :" << std::endl;
	ss << "-----------------Error-----------------" << std::endl;
	ss << m_msgError.toStdString() << std::endl;
	ss << "----------------------------------------" << std::endl;

	return ss.str().data();
}
/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

DBException::~DBException() throw(){}

