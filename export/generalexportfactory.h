#ifndef GENERALEXPORTFACTORY_H
#define GENERALEXPORTFACTORY_H

#include <QStringBuilder>

#include <export/interfaceexportfactory.h>
#include <export/exportfactory.h>
#include <export/exportfactorynotfoundexception.h>
#include <export/exportstrategynotfoundexception.h>
#include <note/classdef.h>

//! Gère l'ensemble des fonctionnalités d'export.
/*!
  Cette classe implémentant le design pattern Singleton contient l'ensembles des stratégies d'exports.
  Elle contient aussi l'ensemble des factory d'export qui permettent d'appliquer la stratégie d'export
  à une note selon le type réel de cette note.

  \version	1.0
  \author	Florian Baune
*/
class GeneralExportFactory
{
	public:
		// Method
		//! Fonction permettant de retourner l'ensemble des nom des stratégies d'export contenuent dans GeneralExportFactory
		/*!
		  \return	La liste de QString des noms des stratégies d'export

		  \version	1.0
		  \author	Florian Baune
		*/
		QList<QString>							getAvailableExportType() const;

		//! Fonction faisant un export complet (avec Header et Footer) d'une note.
		/*!
		  \param	strategyName	Le nom de la stratégie d'export
		  \param	n				La note à exporter
		  \return	La QString résultat de l'export

		  \version	1.0
		  \author	Florian Baune
		*/
		QString									exportNote(const QString& strategyName, const Note& n) const;

		//! Fonction faisant un export complet (avec Header et Footer) d'une note.
		/*!
		  \param	es				La stratégie d'export
		  \param	n				La note à exporter
		  \return	La QString résultat de l'export

		  \version	1.0
		  \author	Florian Baune
		*/
		QString									exportNote(ExportStrategy& es, const Note& n) const;

		//! Fonction faisant un export partiel du contenu d'une note.
		/*!
		  \param	strategyName	Le nom de la stratégie d'export
		  \param	n				La note à exporter
		  \return	La QString résultat de l'export

		  \version	1.0
		  \author	Florian Baune
		*/
		QString									exportNoteAsPart(const QString& strategyName, const Note& n) const;

		//! Fonction faisant un export partiel du contenu d'une note.
		/*!
		  \param	es				La stratégie d'export
		  \param	n				La note à exporter
		  \return	La QString résultat de l'export

		  \version	1.0
		  \author	Florian Baune
		*/
		QString									exportNoteAsPart(ExportStrategy& es, const Note& n) const;

		// Singleton
		//! Fonction retournant l'instance du Singleton GeneralExportFactory
		/*!
		  \return	L'instance de la GeneralExportFactory

		  \version	1.0
		  \author	Florian Baune
		*/
		static GeneralExportFactory&			getInstance();

		//! Fonction détruisant l'instance du Singleton GeneralExportFactory
		/*!
		  \version	1.0
		  \author	Florian Baune
		*/
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
