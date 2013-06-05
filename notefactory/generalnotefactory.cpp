#include "generalnotefactory.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

GeneralNoteFactory::GeneralNoteFactory() : m_factories()
{
	m_factories.insert( Article::staticMetaObject.className(), (InterfaceNoteFactory*)(new NoteFactory<Article>()) );
	m_factories.insert( Document::staticMetaObject.className(), (InterfaceNoteFactory*)(new NoteFactory<Document>()) );
	m_factories.insert( Image::staticMetaObject.className(), (InterfaceNoteFactory*)(new NoteFactory<Image>()) );
	m_factories.insert( Audio::staticMetaObject.className(), (InterfaceNoteFactory*)(new NoteFactory<Audio>()) );
	m_factories.insert( Video::staticMetaObject.className(), (InterfaceNoteFactory*)(new NoteFactory<Video>()) );
}

/********************************************************************
 *                              Method                              *
 ********************************************************************/

InterfaceNoteFactory& GeneralNoteFactory::getFactories(const QString & typeName) const{
	QHash<QString, InterfaceNoteFactory*>::const_iterator it = m_factories.find(typeName);

	if( it==m_factories.end() )
		throw NoteFactoryNotFoundException(typeName.toStdString());
	else
		return **it;
}

Note& GeneralNoteFactory::loadNote(unsigned int id) const{
	// Look for TypeNote of Note corresponding to 'id'.
	DatabaseManager& db = DatabaseManager::getInstance();
	QString typeNote = db.getNoteType(id);

	// Get back the corresponging NoteFactory and load the Note.
	InterfaceNoteFactory& nf = getFactories(typeNote);
	return nf.loadNote(id);
}

void GeneralNoteFactory::saveNote(Note &n) const{
	// Get back the corresponging NoteFactory of Note 'n'.
	InterfaceNoteFactory& nf = getFactories(n.metaObject()->className());

	// Save Note 'n'.
	nf.saveNote(n);
}

void GeneralNoteFactory::deleteNote(Note &n) const{
	// Get back the corresponging NoteFactory of Note 'n'.
	InterfaceNoteFactory& nf = getFactories(n.metaObject()->className());

	// Delete Note 'n'.
	nf.deleteNote(n);
}

/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

GeneralNoteFactory::~GeneralNoteFactory(){
	for(QHash<QString, InterfaceNoteFactory*>::iterator it = m_factories.begin(); it!=m_factories.end(); it++)
		delete *it;
}

/********************************************************************
 *                            Singleton                             *
 ********************************************************************/

GeneralNoteFactory* GeneralNoteFactory::s_inst = NULL;

GeneralNoteFactory& GeneralNoteFactory::getInstance(){
	if( s_inst == NULL )
		s_inst = new GeneralNoteFactory();
	return (*s_inst);
}

void GeneralNoteFactory::destroy(){
	if( s_inst != NULL )
		delete s_inst;
}
