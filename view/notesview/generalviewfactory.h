#ifndef GENERALVIEWFACTORY_H
#define GENERALVIEWFACTORY_H

#include <QHash>
#include <QMap>

#include <singleton.h>
#include <view/notesview/viewfactory.h>
#include <view/notesview/viewfactorynotfoundexception.h>
#include <note/classdef.h>

#include <view/notesview/articleview.h>

class GeneralViewFactory : Singleton<GeneralViewFactory>
{
	public:
		// Method
		QList<QString>							getAvailableViewFactoryType();
		NoteView&								getView(Note& n);
		void                                    deleteView( unsigned int id );

	private:
		// Member
		QHash<QString, InterfaceViewFactory*>	m_factories;
		QMap<unsigned int, NoteView*>			m_views;

		// Method
		InterfaceViewFactory&					getFactories(const QString& typeNote) const;

		// Destructor
		~GeneralViewFactory();
};

#endif // GENERALVIEWFACTORY_H
