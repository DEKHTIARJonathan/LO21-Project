#ifndef NOTESMANAGEREXCEPTION_H
#define NOTESMANAGEREXCEPTION_H

#include <stdexcept>
#include <sstream>
#include <QString>

class NotesManagerException : public std::exception
{

	public:
		// Constructor
		NotesManagerException( const QString & action, const QString & errorMsg );

		// Getter
		const QString &	getAction() const;
		const QString &	getErrorMsg() const;

		// Implementation
		const char*		what() const throw();

		// Destructor
		~NotesManagerException() throw();

	private:
		// Member
		QString			m_action;
		QString			m_errorMsg;

};

#endif
