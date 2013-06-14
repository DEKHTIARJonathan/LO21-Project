#ifndef GENERALVIEWFACTORY_H
#define GENERALVIEWFACTORY_H

#include <QHash>
#include <QMap>

#include <view/notesview/viewfactory.h>
#include <view/notesview/viewfactorynotfoundexception.h>
#include <note/classdef.h>

#include <view/notesview/articleview.h>
#include <view/notesview/imageview.h>
#include <view/notesview/audioview.h>
#include <view/notesview/videoview.h>
#include <view/notesview/documentview.h>

//! Gère l'ensemble des fonctionnalités de construction de vue.
/*!
  Cette classe implémentant le design pattern Singleton contient l'ensembles des factory de vue.

  \version	1.0
  \author	Florian Baune
*/
class GeneralViewFactory
{
	public:
		// Method
		//! Fonction permettant de retourner l'ensemble des noms des types de notes dont on peut générer une vue.
		/*!
		  \return	La liste de QString des noms des types de note

		  \version	1.0
		  \author	Florian Baune
		*/
		QList<QString>							getAvailableViewFactoryType() const;

		//! Fonction récupérant la vue d'une note passé en paramètre.
		/*!
		  Si la vue était déjà créée, la retourne sans autres modifications.

		  \param	n				La note dont on veut construire la vue
		  \return	La référence sur la vue de \a n

		  \version	1.0
		  \author	Florian Baune
		*/
		NoteView&								getView(Note& n);

		//! Fonction désinstanciant la vue (s'il elle existe) d'une note dont on aura passé l'id en paramètre.
		/*!
		  \param	id				L'id de la note

		  \version	1.0
		  \author	Florian Baune
		*/
		void                                    deleteView( unsigned int id );

		//! Fonction désinstanciant toutes les vues déjà instanciées.
		/*!

		  \version	1.0
		  \author	Florian Baune
		*/
		void									flushViews();

		// Singleton
		//! Fonction retournant l'instance du Singleton GeneralViewFactory
		/*!
		  \return	L'instance de la GeneralViewFactory

		  \version	1.0
		  \author	Florian Baune
		*/
		static GeneralViewFactory&				getInstance();

		//! Fonction détruisant l'instance du Singleton GeneralViewFactory
		/*!
		  \version	1.0
		  \author	Florian Baune
		*/
		static void								destroy();

	private:
		// Member
		QHash<QString, InterfaceViewFactory*>	m_factories;
		QMap<unsigned int, NoteView*>			m_views;

		// Method
		InterfaceViewFactory&					getFactories(const QString& typeNote) const;
		void									flush();

		// Destructor
		~GeneralViewFactory();

		// Singleton
		GeneralViewFactory();	// Interdit l'instanciation directe
		GeneralViewFactory(const GeneralViewFactory& nm);	// Interdit la recopie
		GeneralViewFactory&						operator=(const GeneralViewFactory& n);	// Interdit la recopie
		static GeneralViewFactory * s_inst;	// Contient le singleton s'il est instancié
};

#endif // GENERALVIEWFACTORY_H
