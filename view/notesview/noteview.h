#ifndef NOTEVIEW_H
#define NOTEVIEW_H

#include <QWidget>

//! L'interface de vue de note.
/*!
  Cette interface fournit les méthodes nécessaire à l'utilisation d'une Vue dans la fenêtre principale.

  \version	1.0
  \author	Florian Baune
*/
class NoteView : public QWidget
{
		Q_OBJECT

	signals:
		//! Signal permettant de demander à l'application principale d'afficher une note dont on envoie l'id.
		/*!
		  Ce signal sera particulièrement utile dans le cas des documents, afin que l'on puissent demander l'affichage
		  d'une note présente dans le document

		  \param	id		L'id de la note que l'on souhaite se voir afficher

		  \version	1.0
		  \author	Florian Baune
		*/
		void				showNote(unsigned int id);

	public:
		// Constructor
		explicit NoteView(QWidget *parent = 0);

		// Method
		//! Fonction virtuelle pure qui charge le contenu d'une note dans la vue qui lui est associé.
		/*!
		  \param	n		La note dont on veut construire la vue
		  \return	La référence sur la vue nouvellement créée

		  \version	1.0
		  \author	Florian Baune
		*/
		virtual void		loadNoteContent() = 0;

		//! Fonction virtuelle pure active ou désactive le mode édition de la vue.
		/*!
		  \param	b		Booléen qui vaut vraie si on veut éditer et faux dans le cas contraire.

		  \version	1.0
		  \author	Florian Baune
		*/
		virtual void		setEditMode(bool b) = 0;

		//! Fonction virtuelle pure qui transfère les changements apporté à la partie vue dans la note qui lui est associée.
		/*!

		  \version	1.0
		  \author	Florian Baune
		*/
		virtual void		saveChanges() = 0;

		// Destructor
		virtual ~NoteView();
};

#endif // NOTEVIEW_H
