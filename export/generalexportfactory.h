#ifndef GENERALEXPORTFACTORY_H
#define GENERALEXPORTFACTORY_H

#include <QStringBuilder>

#include <export/interfaceexportfactory.h>
#include <export/exportfactory.h>
#include <export/exportfactorynotfoundexception.h>
#include <export/exportstrategynotfoundexception.h>
#include <note/classdef.h>

class GeneralExportFactory
{
	public:
		// Method
		QList<QString>							getAvailableExportType() const;
		QString									exportNote(const QString& strategyName, const Note& n) const;
		QString									exportNote(ExportStrategy& es, const Note& n) const;
		QString									exportNoteAsPart(const QString& strategyName, const Note& n) const;
		QString									exportNoteAsPart(ExportStrategy& es, const Note& n) const;

		// Singleton
		static GeneralExportFactory&			getInstance();
		static void								destroy();

	private:
		// Member
		QHash<QString, InterfaceExportFactory*>	m_factories;
		QHash<QString, ExportStrategy*>			m_strategies;

		// Method
		InterfaceExportFactory&					getFactory(const QString& typeNote) const;
		ExportStrategy&							getStrategy(const QString & strategyName) const;

		// Destructor
		~GeneralExportFactory();

		// Singleton
		GeneralExportFactory();	// Interdit l'instanciation directe
		GeneralExportFactory(const GeneralExportFactory& nm);	// Interdit la recopie
		GeneralExportFactory&					operator=(const GeneralExportFactory& n);	// Interdit la recopie
		static GeneralExportFactory*			s_inst;	// Contient le singleton s'il est instancié
};

#endif // GENERALEXPORTFACTORY_H
