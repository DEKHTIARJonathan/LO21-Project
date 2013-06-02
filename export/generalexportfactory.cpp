#include "generalexportfactory.h"

#include "export/exporthtml.h"
#include "export/exporttex.h"
#include "export/exporttext.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

GeneralExportFactory::GeneralExportFactory() : m_factories(), m_strategies()
{
	// Strategies
	m_strategies.insert(	"html",									(ExportStrategy*)(new ExportHTML())	);
	m_strategies.insert(	"tex",									(ExportStrategy*)(new ExportTex())	);
	m_strategies.insert(	"txt",									(ExportStrategy*)(new ExportText())	);

	// Factories
	m_factories.insert(		Article::staticMetaObject.className(),	(InterfaceExportFactory*)(new ExportFactory<Article>())		);
	m_factories.insert(		Document::staticMetaObject.className(),	(InterfaceExportFactory*)(new ExportFactory<Document>())	);
	m_factories.insert(		Image::staticMetaObject.className(),	(InterfaceExportFactory*)(new ExportFactory<Image>())		);
	m_factories.insert(		Audio::staticMetaObject.className(),	(InterfaceExportFactory*)(new ExportFactory<Audio>())		);
	m_factories.insert(		Video::staticMetaObject.className(),	(InterfaceExportFactory*)(new ExportFactory<Video>())		);
}

/********************************************************************
 *                              Method                              *
 ********************************************************************/

InterfaceExportFactory& GeneralExportFactory::getFactory(const QString & typeName) const{
	QHash<QString, InterfaceExportFactory*>::const_iterator it = m_factories.find(typeName);

	if( it==m_factories.end() )
		throw ExportFactoryNotFoundException(typeName);
	else
		return **it;
}

ExportStrategy& GeneralExportFactory::getStrategy(const QString & strategyName) const{
	QHash<QString, ExportStrategy*>::const_iterator it = m_strategies.find(strategyName);

	if( it==m_strategies.end() )
		throw ExportStrategyNotFoundException(strategyName);
	else
		return **it;
}

QString GeneralExportFactory::exportNote(const QString& strategyName, const Note& n) const{
	// Get back the corresponging ExportStrategy and export the Note.
	ExportStrategy& es = getStrategy(strategyName);
	return	exportNote(es,n);
}

QString GeneralExportFactory::exportNote(ExportStrategy& es, const Note& n) const{
	// Get back the corresponging ExportFactory and export the Note.
	InterfaceExportFactory& ef = getFactory(n.metaObject()->className());
	return	es.header() %
			ef.exportAsPart(es, n) %
			es.footer();
}

QString GeneralExportFactory::exportNoteAsPart(const QString& strategyName, const Note& n, unsigned int level) const{
	// Get back the corresponging ExportStrategy and export the Note.
	ExportStrategy& es = getStrategy(strategyName);
	return	exportNoteAsPart(es,n,level);
}

QString GeneralExportFactory::exportNoteAsPart(ExportStrategy& es, const Note& n, unsigned int level) const{
	// Get back the corresponging ExportFactory and export the Note.
	InterfaceExportFactory& ef = getFactory(n.metaObject()->className());
	return ef.exportAsPart(es, n, level);
}

/********************************************************************
 *                            Singleton                             *
 ********************************************************************/

GeneralExportFactory* GeneralExportFactory::s_inst = NULL;

GeneralExportFactory& GeneralExportFactory::getInstance(){
	if( s_inst == NULL )
		s_inst = new GeneralExportFactory();
	return (*s_inst);
}

void GeneralExportFactory::destroy(){
	if( s_inst != NULL )
		delete s_inst;
}

