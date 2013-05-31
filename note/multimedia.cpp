#include "multimedia.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

// Generic MultiMedia constructor
MultiMedia::MultiMedia( unsigned int id ) : Note(id), m_description(), m_path()
{
}

/********************************************************************
 *                              Getter                              *
 ********************************************************************/

const QString &	MultiMedia::getDescription() const{	return m_description;	}
const QString &	MultiMedia::getPath() const{		return m_path;			}

/********************************************************************
 *                              Setter                              *
 ********************************************************************/

void	MultiMedia::setDescription( const QString & description){	m_description	= description;	}
void	MultiMedia::setPath( const QString & path){					m_path			= path;			}

/********************************************************************
 *                              Method                              *
 ********************************************************************/


