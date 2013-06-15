#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include <QMap>
#include <QString>

#include <note/note.h>
#include <notefactory/generalnotefactory.h>
#include <notemanager/notesmanagerexception.h>

using namespace std;

//! Gère l'ensemble des instances des notes du programme.
/*!
  Cette classe implémentant le design pattern Singleton contient l'ensembles des instances de notes.
  Elle sert d'interface avec la factory des Notes ainsi qu'avec le support de sauvegarde représenté par DatabaseManager.
  Elle va notamment permettre de charger les notes au fur et à mesure des besoins de l'utilisateur.
  Elle évitera aussi qu'une même note ne soit charger deux fois depuis le support de sauvegarde.

  \version	1.0
  \author	Florian Baune & Jonathan Dekhtiar
*/
class NotesManager
{

	public:
		// Method
		//! Fonction permettant d'obtenir une nouvelle note.
		/*!
		  Si le nom du type de note ne possède pas de factory, cette fonction retourne une NoteFactoryNotFoundException.
		  Cette fonction est aussi suceptible de renvoyer des exceptions inhérentes à l'utilisation de la DatabaseManager.
		  \param	typeNote	Le nom type de note dont on souhaite obtenir la factory.
		  \return	La liste de QString des noms des stratégies d'export

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		Note&							getNewNote(const QString &typeNote);

		//! Fonction qui gère le chargement d'une note à partir de son id.
		/*!
		  Cette dernière utilise une GeneralNoteFactory qui utilise le singleton DatabaseManager, ainsi elle est susceptible de retourner toutes les exceptions
		  possibles inhérentes à l'utilisation des fonctionnalités de ce dernier.
		  En particulier, ici, une exception de ce type sera retourner si l'id passé en paramètre n'est pas contenue sur le support de sauvegarde.

		  \param	L'id de la note que l'on souhaite charger.
		  \return	La Note que l'on vient de charger

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		Note&							getNote(unsigned int id);

		//! Fonction qui gère la sauvegarde d'une note.
		/*!
		  Cette dernière utilise une GeneralNoteFactory qui utilise le singleton DatabaseManager, ainsi elle est susceptible de retourner toutes les exceptions
		  possibles inhérentes à l'utilisation des fonctionnalités de ce dernier.

		  \param	La note que l'on souhaite sauvegarder sur le support de sauvegarde.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void							saveNote(Note& n);

		//! Fonction qui gère la mise à la corbeille d'une note donnée en paramètre.
		/*!
		  Cette dernière utilise une NoteFectory qui utilise le singleton DatabaseManager, ainsi elle est susceptible de retourner toutes les exceptions
		  possibles inhérentes à l'utilisation des fonctionnalités de ce dernier.

		  \param	La note que l'on souhaite mettre à la corbeille.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void							putToTrash(Note& n);

		//! Fonction qui gère la destruction et la désinstentiation de toutes les notes présentent dans la corbeille.
		/*!
		  Cette dernière utilise une NoteFectory qui utilise le singleton DatabaseManager, ainsi elle est susceptible de retourner toutes les exceptions
		  possibles inhérentes à l'utilisation des fonctionnalités de ce dernier.

		  \param	La liste des Ids des notes contenues dans la corbeille.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void							emptyTrash(const std::vector< pair <unsigned int, QString > >& trash);

		//! Fonction qui desinstancie l'ensemble des notes contenues dans le NotesManager.
		/*!
		  Cette dernière utilise une NoteFectory qui utilise le singleton DatabaseManager, ainsi elle est susceptible de retourner toutes les exceptions
		  possibles inhérentes à l'utilisation des fonctionnalités de ce dernier.

		  \param	La note que l'on souhaite désinstancier.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void							flush();

		// Singleton
		//! Fonction retournant l'instance du Singleton NotesManager
		/*!
		  \return	L'instance de la NotesManager

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		static NotesManager&			getInstance();

		//! Fonction retournant l'instance du Singleton NotesManager
		/*!
		  \return	L'instance de la NotesManager

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		static void						destroy();

	private:
		// Member
		QMap<unsigned int,Note*>		m_loadedNotes;

		// Destructor
		~NotesManager();

		// Singleton
		NotesManager();	// Interdit l'instanciation directe
		NotesManager(const NotesManager& nm);	// Interdit la recopie
		NotesManager&				operator=(const NotesManager& n);	// Interdit la recopie
		static NotesManager * s_inst;	// Contient le singleton s'il est instancie

};

#endif
