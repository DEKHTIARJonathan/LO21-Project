#ifndef EXPORTSTRATEGYNOTFOUNDEXCEPTION_H
#define EXPORTSTRATEGYNOTFOUNDEXCEPTION_H

#include <stdexcept>
#include <sstream>
#include <QString>
#include "exportfileexception.h"

class ExportStrategyNotFoundException : public std::exception
{

	public:
		// Constructor
		ExportStrategyNotFoundException( const QString & esName );

		// Getter
		const QString &		getEsName() const;

		// Implementation
		const char*			what() const throw();

		// Destructor
		~ExportStrategyNotFoundException() throw();

	private:
		// Member
		QString			m_esName;

};

#endif
