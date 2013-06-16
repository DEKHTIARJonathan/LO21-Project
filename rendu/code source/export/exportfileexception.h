#ifndef EXPORTFILEEXCEPTION_H
#define EXPORTFILEEXCEPTION_H

#include <stdexcept>
#include <sstream>
#include <QString>

class ExportFileException : public std::exception
{

	public:
		// Constructor
		ExportFileException( const QString & action, const QString & error );

		// Getter
		const QString &	getAction() const;
		const QString &	getError() const;

		// Implementation
		const char*		what() const throw();

		// Destructor
		~ExportFileException() throw();

	private:
		// Member
		QString			m_action;
		QString			m_error;

};

#endif
