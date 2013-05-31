#ifndef DOCUMENTINDEXOUTOFARRAYEXCEPTION_H
#define DOCUMENTINDEXOUTOFARRAYEXCEPTION_H

#include <stdexcept>
#include <sstream>
#include <QString>

class DocumentIndexOutOfArrayException : public std::exception
{

	public:
		// Constructor
		DocumentIndexOutOfArrayException( unsigned int index, const QString & docName );

		// Getter
		unsigned int	getIndex() const;
		const QString &	getDocName() const;

		// Implementation
		const char*		what() const throw();

		// Destructor
		~DocumentIndexOutOfArrayException() throw();

	private:
		// Member
		unsigned int	m_index;
		QString			m_docName;

};

#endif
