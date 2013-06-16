#ifndef EXPORTFACTORYNOTFOUNDEXCEPTION_H
#define EXPORTFACTORYNOTFOUNDEXCEPTION_H

#include <stdexcept>
#include <sstream>
#include <QString>

class ExportFactoryNotFoundException : public std::exception
{

	public:
		// Constructor
		ExportFactoryNotFoundException( const QString & typeName );

		// Getter
		const QString &	getTypeName() const;

		// Implementation
		const char*		what() const throw();

		// Destructor
		~ExportFactoryNotFoundException() throw();

	private:
		// Member
		QString			m_typeName;

};

#endif
