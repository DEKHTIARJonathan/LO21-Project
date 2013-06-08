#include "generalviewfactory.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

GeneralViewFactory::GeneralViewFactory() : m_factories()
{
	m_factories.insert( Article::staticMetaObject.className(), (InterfaceViewFactory*)(new ViewFactory<Article, ArticleView>()) );
	m_factories.insert( Image::staticMetaObject.className(), (InterfaceViewFactory*)(new ViewFactory<Image, ImageView>()) );
	m_factories.insert( Audio::staticMetaObject.className(), (InterfaceViewFactory*)(new ViewFactory<Audio, AudioView>()) );
	m_factories.insert( Video::staticMetaObject.className(), (InterfaceViewFactory*)(new ViewFactory<Video, VideoView>()) );
	m_factories.insert( Document::staticMetaObject.className(), (InterfaceViewFactory*)(new ViewFactory<Document, DocumentView>()) );
}

/********************************************************************
 *                              Method                              *
 ********************************************************************/

QList<QString> GeneralViewFactory::getAvailableViewFactoryType() const{
	return m_factories.keys();
}

InterfaceViewFactory& GeneralViewFactory::getFactories(const QString & typeName) const{
	QHash<QString, InterfaceViewFactory*>::const_iterator it = m_factories.find(typeName);

	if( it==m_factories.end() )
		throw ViewFactoryNotFoundException(typeName);
	else
		return **it;
}

NoteView& GeneralViewFactory::getView(Note& n){
	// Look for already created view
	QMap<unsigned int, NoteView*>::iterator f = m_views.find(n.getId());

	// And load it if exist
	if( f!=m_views.end() )
		return **f;

	// Get back the corresponging ViewFactory and load it.
	InterfaceViewFactory& vf = getFactories(n.metaObject()->className());
	NoteView& view = vf.buildNoteView(n);
	m_views.insert(n.getId(),&view);
	return view;
}

void GeneralViewFactory::deleteView(unsigned int id){
	// Look for corresponding view
	QMap<unsigned int, NoteView*>::iterator f = m_views.find(id);

	if( f!=m_views.end() ){ // And delete here if exist
		NoteView* v = *f;
		m_views.erase(f);
		delete (v);
	}
}

void GeneralViewFactory::flush(){
	for(QHash<QString, InterfaceViewFactory*>::iterator it = m_factories.begin(); it!=m_factories.end(); it++)
		delete *it;
}

/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

GeneralViewFactory::~GeneralViewFactory(){
	flush();
}

/********************************************************************
 *                            Singleton                             *
 ********************************************************************/

GeneralViewFactory* GeneralViewFactory::s_inst = NULL;

GeneralViewFactory& GeneralViewFactory::getInstance(){
	if( s_inst == NULL )
		s_inst = new GeneralViewFactory();
	return (*s_inst);
}

void GeneralViewFactory::destroy(){
	if( s_inst != NULL )
		delete s_inst;
}

