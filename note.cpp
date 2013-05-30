#include "note.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

// Generic Note constructor
Note::Note( unsigned int id, const QString & title, bool loaded, bool modified )
{
	m_id		= id;
	m_title		= title;
	m_loaded	= loaded;
	m_modified	= modified;
}

/********************************************************************
 *                              Getter                              *
 ********************************************************************/

unsigned int	Note::getId() const{		return m_id;		}
const QString &	Note::getTitle() const{		return m_title;		}
bool			Note::getLoaded() const{	return m_loaded;	}
bool			Note::getModified() const{	return m_modified;	}

/********************************************************************
 *                              Setter                              *
 ********************************************************************/

void	Note::setTitle( const QString & title){	m_title	= title;	}

/********************************************************************
 *                              Method                              *
 ********************************************************************/


