#include "note.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

Note::Note( unsigned int id ) : QObject(), m_modified(false), m_id(id) , m_title()
{
}

Note::Note( unsigned int id, const QString & title ) : QObject(), m_modified(false), m_id(id) , m_title(title)
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

void Note::setTitle( const QString & title){	m_title	= title;
												m_modified = true;	}

/********************************************************************
 *                             Operator                             *
 ********************************************************************/

bool Note::operator==(const Note& n) const{
	return this->m_id == n.m_id;
}

/********************************************************************
 *                              Method                              *
 ********************************************************************/

void Note::confirmSaving(){						m_modified	= false;}

/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

Note::~Note(){
}
