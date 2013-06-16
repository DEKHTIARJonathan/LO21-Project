#include "article.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

Article::Article( unsigned int id ) : Note(id), m_text()
{
}

/********************************************************************
 *                              Getter                              *
 ********************************************************************/

const QString &	Article::getText() const{	return m_text;	}

/********************************************************************
 *                              Setter                              *
 ********************************************************************/

void	Article::setText( const QString & text){	m_text	= text;
													m_modified = true;	}

/********************************************************************
 *                              Method                              *
 ********************************************************************/


