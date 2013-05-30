#include "note.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

// Generic Note constructor
Note::Note( unsigned int id ) : m_id(id), m_title(), m_modified(false)
{
}

Note::Note( unsigned int id, const QString & title ) : m_id(id), m_title(title), m_modified(false)
{
}

/********************************************************************
 *                              Getter                              *
 ********************************************************************/

unsigned int	Note::getId() const{		return m_id;		}
const QString &	Note::getTitle() const{		return m_title;		}
bool			Note::isModified() const{	return m_modified;	}

/********************************************************************
 *                              Setter                              *
 ********************************************************************/

void	Note::setTitle( const QString & title){	m_title	= title;	}

/********************************************************************
 *                              Method                              *
 ********************************************************************/

