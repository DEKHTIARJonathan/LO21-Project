#ifndef DBEXCEPTION_H
#define DBEXCEPTION_H

#include <stdexcept>
#include <sstream>
#include <QString>

class DBException : public std::exception
{

	public:
		// Constructor
		DBException( const QString & procedure, const QString & msgError );

		// Getter
		const QString &	getProcedure() const;
		const QString &	getMsgError() const;

		// Implementation
		const char*		what() const throw();

		// Destructor
		~DBException() throw();

	private:
		// Member
		QString			m_procedure;
		QString			m_msgError;

};

#endif
