#ifndef INTERFACENOTEFACTORY_H
#define INTERFACENOTEFACTORY_H

#include <note/note.h>

//! L'interface qui sera réimplémenté par la classe template NoteFactory.
/*!
  Cette interface fournit les méthodes nécessaires à la création, la sauvegarde, le chargement et la destruction d'une note.

  \version	1.0
  \author	Florian Baune & Jonathan Dekhtiar
*/
class InterfaceNoteFactory
{
	public:

		//! Fonction virtuelle pure qui gère la création d'une nouvelle note.
		/*!
		  \return	La Note que l'on vient de créer

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		virtual Note&		buildNewNote() = 0;

		//! Fonction virtuelle pure qui gère le chargement d'une note à partir de son id.
		/*!
		  \param	L'id de la note que l'on souhaite charger.
		  \return	La Note que l'on vient de charger

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		virtual Note&		loadNote(unsigned int id) = 0;

		//! Fonction virtuelle pure qui gère la sauvegarde d'une note.
		/*!
		  \param	La note que l'on souhaite sauvegarder sur le support de sauvegarde.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		virtual void		saveNote(Note& n) = 0;

		//! Fonction virtuelle pure qui gère la désinstentiation d'une note.
		/*!
		  \param	La note que l'on souhaite désinstencier.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		virtual void		deleteNote(Note& n) = 0;

};

#endif // INTERFACENOTEFACTORY_H
