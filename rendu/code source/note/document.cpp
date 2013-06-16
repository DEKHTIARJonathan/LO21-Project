#include "document.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

Document::Document( unsigned int id ) : Note(id), m_notes()
{
}

/********************************************************************
 *                              Method                              *
 ********************************************************************/

bool Document::containNote( unsigned int id ) const{
	for( vector<Note*>::const_iterator it = m_notes.begin(); it!=m_notes.end(); it++ )
		if( (*it)->getId() == id )
			return true;
	return false;
}

void Document::addNote( Note& n){
	if( !this->containNote(n.getId()) ){
		m_notes.push_back(&n);
		m_modified = true;
	}
}

Note& Document::getNote(unsigned int i) const{
	if( i>=m_notes.size() )
		throw DocumentIndexOutOfArrayException(i, this->getTitle());
	else
		return (*m_notes[i]);
}

void Document::removeNote(unsigned int id){
	for( vector<Note*>::iterator it = m_notes.begin(); it!=m_notes.end(); it++ )
		if( (*it)->getId() == id ){
			m_notes.erase(it);
			m_modified = true;
			break;
		}
}

void Document::flushNotes(){
	m_notes.clear();
	m_modified = true;
}

vector<Note*>::iterator Document::begin(){
	return m_notes.begin();
}

vector<Note*>::const_iterator Document::begin() const{
	return m_notes.begin();
}

vector<Note*>::iterator Document::end(){
	return m_notes.end();
}

vector<Note*>::const_iterator Document::end() const{
	return m_notes.end();
}

