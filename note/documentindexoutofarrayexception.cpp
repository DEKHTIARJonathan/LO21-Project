#include "documentindexoutofarrayexception.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

// Generic DocumentIndexOutOfArrayException constructor
DocumentIndexOutOfArrayException::DocumentIndexOutOfArrayException( unsigned int index, const QString & docName ) : std::exception()
{
	m_index		= index;
	m_docName	= docName;
}

/********************************************************************
 *                              Getter                              *
 ********************************************************************/

unsigned int	DocumentIndexOutOfArrayException::getIndex() const{		return m_index;		}
const QString &	DocumentIndexOutOfArrayException::getDocName() const{	return m_docName;	}

/********************************************************************
 *                          Implementation                          *
 ********************************************************************/

const char* DocumentIndexOutOfArrayException::what() const throw(){

	std::stringstream ss;

	ss << "L'index " << m_index << " est invalide pour le Document '" << m_docName.toStdString() << "'." << std::endl;

	return ss.str().data();
}
/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

DocumentIndexOutOfArrayException::~DocumentIndexOutOfArrayException() throw(){}

