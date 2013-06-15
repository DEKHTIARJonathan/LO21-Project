#ifndef GENERALNOTEFACTORY_H
#define GENERALNOTEFACTORY_H

#include <QHash>

#include <notefactory/interfacenotefactory.h>
#include <notefactory/notefactory.h>
#include <notefactory/notefactorynotfoundexception.h>

using namespace std;

//! Gère l'ensemble des fonctionnalités nécessaire à la gestion des données des notes.
/*!
  Cette classe implémentant le design pattern Singleton contient l'ensembles des factory permettant de gérer les différents types de note.
  Elle permettra notamment, la création d'une nouvelle note d'un certain type, le chargement/sauvegarde d'une note et la destruction d'une note.

  \version	1.0
  \author	Florian Baune & Jonathan Dekhtiar
*/
class GeneralNoteFactory
{
	public:
		// Method
		//! Fonction permettant de retourner une factory pour un certain type de note.
		/*!
		  Si le nom du type de note ne possède pas de factory, cette fonction retourne une NoteFactoryNotFoundException.
		  \param	typeNote	Le nom type de note dont on souhaite obtenir la factory.
		  \return	La liste de QString des noms des stratégies d'export

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		InterfaceNoteFactory&					getFactories(const QString& typeNote) const;

		//! Fonction qui gère le chargement d'une note à partir de son id.
		/*!
		  Cette dernière utilise une NoteFactory qui utilise le singleton DatabaseManager, ainsi elle est susceptible de retourner toutes les exceptions
		  possibles inhérentes à l'utilisation des fonctionnalités de ce dernier.

		  \param	L'id de la note que l'on souhaite charger.
		  \return	La Note que l'on vient de charger

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		Note&									loadNote(unsigned int id) const;

		//! Fonction qui gère la sauvegarde d'une note.
		/*!
		  Cette dernière utilise une NoteFectory qui utilise le singleton DatabaseManager, ainsi elle est susceptible de retourner toutes les exceptions
		  possibles inhérentes à l'utilisation des fonctionnalités de ce dernier.

		  \param	La note que l'on souhaite sauvegarder sur le support de sauvegarde.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void									saveNote(Note& n) const;

		//! Fonction qui gère la destruction et la désinstentiation d'une note aussi bien dans la mémoire courante que dans le support de de sauvegarde.
		/*!
		  Cette dernière utilise une NoteFectory qui utilise le singleton DatabaseManager, ainsi elle est susceptible de retourner toutes les exceptions
		  possibles inhérentes à l'utilisation des fonctionnalités de ce dernier.

		  \param	La note que l'on souhaite détruire sur le support de sauvegarde.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void									deleteNote(Note& n) const;

		// Singleton
		//! Fonction retournant l'instance du Singleton GeneralNoteFactory
		/*!
		  \return	L'instance de la GeneralNoteFactory

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		static GeneralNoteFactory&				getInstance();

		//! Fonction retournant l'instance du Singleton GeneralNoteFactory
		/*!
		  \return	L'instance de la GeneralNoteFactory

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		static void								destroy();

	private:
		// Member
		QHash<QString, InterfaceNoteFactory*>	m_factories;

		// Destructor
		~GeneralNoteFactory();

		// Singleton
		GeneralNoteFactory();	// Interdit l'instanciation directe
		GeneralNoteFactory(const GeneralNoteFactory& nm);	// Interdit la recopie
		GeneralNoteFactory&						operator=(const GeneralNoteFactory& n);	// Interdit la recopie
		static GeneralNoteFactory * s_inst;	// Contient le singleton s'il est instancié
};

#endif // GENERALNOTEFACTORY_H
