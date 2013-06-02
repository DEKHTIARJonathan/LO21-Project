#ifndef GENERALNOTEFACTORY_H
#define GENERALNOTEFACTORY_H

#include <QHash>

#include <notefactory/interfacenotefactory.h>
#include <notefactory/notefactory.h>
#include <notefactory/notefactorynotfoundexception.h>

using namespace std;

class GeneralNoteFactory
{
	public:
		// Method
		InterfaceNoteFactory&					getFactories(const QString& typeNote) const;

		// Singleton
		static GeneralNoteFactory&				getInstance();
		static void								destroy();

	private:
		// Member
		QHash<QString, InterfaceNoteFactory*>	m_factories;

		// Singleton
		GeneralNoteFactory();	// Interdit l'instanciation directe
		GeneralNoteFactory(const GeneralNoteFactory& nm);	// Interdit la recopie
		GeneralNoteFactory&						operator=(const GeneralNoteFactory& n);	// Interdit la recopie
		static GeneralNoteFactory * s_inst;	// Contient le singleton s'il est instancié
};

#endif // GENERALNOTEFACTORY_H
