#ifndef EXPORTSTRATEGYNOTFOUNDEXCEPTION_H
#define EXPORTSTRATEGYNOTFOUNDEXCEPTION_H

#include <stdexcept>
#include <sstream>
#include <QString>

class ExportStrategyNotFoundException : public std::exception
{

	public:
		// Constructor
		ExportStrategyNotFoundException( const std::string & esName );

		// Getter
		const std::string &	getEsName() const;

		// Implementation
		const char*			what() const throw();

		// Destructor
		~ExportStrategyNotFoundException() throw();

	private:
		// Member
		std::string			m_esName;

};

#endif
