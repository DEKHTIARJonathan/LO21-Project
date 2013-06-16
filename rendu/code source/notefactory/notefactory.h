#ifndef NOTEFACTORY_H
#define NOTEFACTORY_H

#include <notefactory/interfacenotefactory.h>
#include <dbmanager/databasemanager.h>

//! Classe template implémentant l'interface InterfaceNoteFactory
/*!
  Cette classe factory template implémente la gestion d'une note du type passé en argument template.

  \version	1.0
  \author	Florian Baune & Jonathan Dekhtiar
*/
template<class NoteType>
class NoteFactory : public InterfaceNoteFactory
{
	public:

		//! Fonction qui gère la création d'une nouvelle note.
		/*!
		  Cette dernière utilise le singleton DatabaseManager, ainsi elle est susceptible de retourner toutes les exceptions
		  possibles inérantes à l'utilisation des fonctionnalités de ce dernier.

		  \return	La Note que l'on vient de créer

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		Note& buildNewNote(){
			DatabaseManager& db = DatabaseManager::getInstance();

			unsigned int id = db.insertNote(NoteType::staticMetaObject.className());
			NoteType& n = *(new NoteType(id));
			n.setTitle(QString("New ") + NoteType::staticMetaObject.className());
			saveNote(n);

			return n;
		}

		//! Fonction qui gère le chargement d'une note à partir de son id.
		/*!
		  Cette dernière utilise le singleton DatabaseManager, ainsi elle est susceptible de retourner toutes les exceptions
		  possibles inérantes à l'utilisation des fonctionnalités de ce dernier.

		  \param	L'id de la note que l'on souhaite charger.
		  \return	La Note que l'on vient de charger

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		Note& loadNote(unsigned int id){
			DatabaseManager& db = DatabaseManager::getInstance();

			NoteType& n = *(new NoteType(id));
			db.fillNote( n );

			return n;
		}

		//! Fonction qui gère la sauvegarde d'une note.
		/*!
		  Cette dernière utilise le singleton DatabaseManager, ainsi elle est susceptible de retourner toutes les exceptions
		  possibles inérantes à l'utilisation des fonctionnalités de ce dernier.

		  \param	La note que l'on souhaite sauvegarder sur le support de sauvegarde.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void saveNote(Note &n){
			DatabaseManager& db = DatabaseManager::getInstance();

			NoteType& casted_n = dynamic_cast<NoteType&> (n);
			db.updateNote(casted_n);
			n.confirmSaving();
		}

		//! Fonction qui gère la désinstentiation d'une note.
		/*!
		  On remarque que cette fonction n'est pas essentielle, du fait que les destructeurs des notes sont virtuelles.
		  Cependant, on la conservera pour des raisons d'évolutivités.
		  Ainsi, si des opérations doivent être effectués avant ou après la désinstanciation, il suffirat de seulement modifier cette partie du code.

		  \param	La note que l'on souhaite désinstancier.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void deleteNote(Note &n){
			delete &n;
		}

};

#endif // NOTEFACTORY_H
