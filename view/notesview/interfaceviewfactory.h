#ifndef INTERFACEVIEWFACTORY_H
#define INTERFACEVIEWFACTORY_H

#include <note/note.h>
#include <view/notesview/noteview.h>


//! L'interface qui sera réimplémenté par la classe template ViewFactory.
/*!
  Cette interface fournit la méthode nécessaire à l'utilisation d'une View Strategy.

  \version	1.0
  \author	Florian Baune
*/
class InterfaceViewFactory
{
	public:
		//! Fonction virtuelle pure qui génère une vue à partir d'une note.
		/*!
		  \param	n		La note dont on veut construire la vue
		  \return	La référence sur la vue nouvellement créée

		  \version	1.0
		  \author	Florian Baune
		*/
		virtual NoteView&	buildNoteView(Note& n) = 0;
};

#endif // INTERFACEVIEWFACTORY_H
