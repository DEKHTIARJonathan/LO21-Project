#ifndef VIEWFACTORYNOTFOUNDEXCEPTION_H
#define VIEWFACTORYNOTFOUNDEXCEPTION_H

#include <stdexcept>
#include <sstream>
#include <QString>

class ViewFactoryNotFoundException : public std::exception
{

	public:
		// Constructor
		ViewFactoryNotFoundException( const QString & typeName );

		// Getter
		const QString &	getTypeName() const;

		// Implementation
		const char*		what() const throw();

		// Destructor
		~ViewFactoryNotFoundException() throw();

	private:
		// Member
		QString			m_typeName;

};

#endif
