#ifndef NOTEFACTORYNOTFOUNDEXCEPTION_H
#define NOTEFACTORYNOTFOUNDEXCEPTION_H

#include <stdexcept>
#include <sstream>

using namespace std;

class NoteFactoryNotFoundException : public std::exception
{

	public:
		// Constructor
		NoteFactoryNotFoundException( const string & factoryName );

		// Getter
		const string &	getFactoryName() const;

		// Implementation
		const char*		what() const throw();

		// Destructor
		~NoteFactoryNotFoundException() throw();

	private:
		// Member
		string			m_factoryName;

};

#endif
