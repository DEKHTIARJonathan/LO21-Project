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

class GeneralViewFactory
{
	public:
		// Method
		QList<QString>							getAvailableViewFactoryType() const;
		NoteView&								getView(Note& n);
		void                                    deleteView( unsigned int id );
		void									flushViews();

		// Singleton
		static GeneralViewFactory&				getInstance();
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
