#ifndef GENERALNOTEFACTORY_H
#define GENERALNOTEFACTORY_H

#include <vector>

#include <dbmanager/databasemanager.h>

using namespace std;

class GeneralNoteFactory
{
	public:
		// Method


		// Singleton
		static GeneralNoteFactory&		getInstance();
		static void						destroy();

	private:

		// Singleton
		GeneralNoteFactory();	// Interdit l'instanciation directe
		GeneralNoteFactory(const GeneralNoteFactory& nm);	// Interdit la recopie
		GeneralNoteFactory&				operator=(const GeneralNoteFactory& n);	// Interdit la recopie
		static GeneralNoteFactory * s_inst;	// Contient le singleton s'il est instancié
};

#endif // GENERALNOTEFACTORY_H
