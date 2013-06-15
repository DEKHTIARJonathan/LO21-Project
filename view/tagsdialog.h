#ifndef TAGSDIALOG_H
#define TAGSDIALOG_H

#include <QDialog>
#include <QInputDialog>
#include <dbmanager/databasemanager.h>
#include <view/listnoteviewitem.h>

namespace Ui {
class TagsDialog;
}


//! Cette vue gère l'affichage, l'ajout ainsi que la séléction et désélection de tags pour une note donnée.
/*!
  Le fonctionnemant de ce dialog est assez simple.
  A l'ouverture, il affiche l'ensemble des tags disponnibles tout en cochant les tags déjà attribué à la note courante.
  Ensuite il permet à l'utilisateur de cocher ou décocher facilement les tags.
  De plus, elle permet l'ajout d'un tag via le bouton "Add Tag" qui déclenche le slot addTag(), ce dernier ouvre un
  autre dialog qui demande une chaine de caractère, si cette dernière est correcte, elle est ajoutée en tant que Tag.
  Enfin, si le bouton "Cancel" est appuyer le dialog se ferme sans d'autres actions.
  Par contre, si le bouton "Ok" est appuyer, la valeur du booléen "isCancelled" est mise à jours.
  Cette valeur pourra donc être récupérée par la fonction appelante afin de décider s'il faut sauvegarder les nouvelles
  attributions tags.

  \version	1.0
  \author	Florian Baune & Jonathan Dekhtiar
*/
class TagsDialog : public QDialog
{
	Q_OBJECT

	public slots:
		void										addTag();
		void										ok();

	public:
		// Constructor
		explicit TagsDialog(Note &n, QWidget *parent = 0);

		// Getter
		const QStringList &							getSelectedTags() const;
		bool										isCancelled() const;

		// Destructor
		~TagsDialog();

	private:
		// Member
		Ui::TagsDialog*								ui;
		Note&										m_note;
		bool										m_isCancelled;
		QStringList									m_tagsList;
		QStringList									m_selectedTags;
};

#endif // TAGSDIALOG_H
