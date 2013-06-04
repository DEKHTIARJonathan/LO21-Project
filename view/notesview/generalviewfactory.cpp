#include "generalviewfactory.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

GeneralViewFactory::GeneralViewFactory() : m_factories()
{
	m_factories.insert( Article::staticMetaObject.className(), (InterfaceViewFactory*)(new ViewFactory<Article, ArticleView>()) );
}

/********************************************************************
 *                              Method                              *
 ********************************************************************/

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

	if( f!=m_views.end() ) // And load it if exist
		return **f;

	// Get back the corresponging ViewFactory and load it.
	InterfaceViewFactory& vf = getFactories(n.metaObject()->className());
	return vf.buildNoteView(n);
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

