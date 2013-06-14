#ifndef TRASHDIALOG_H
#define TRASHDIALOG_H

#include <QDialog>
#include <dbmanager/databasemanager.h>
#include <notemanager/notesmanager.h>
#include <view/listnoteviewitem.h>

namespace Ui {
class TrashDialog;
}

//! Cette vue gère l'affichage, la restauration et la suppression des notes contenues dans la corbeille.
/*!
  Le fonctionnemant de ce dialog est assez simple.
  A l'ouverture, il affiche l'ensemble des notes contenues dans la corbeille.
  Ensuite il a trois cas de figure qui entraînent la fermeture du dialog:
	- l'appuie sur le bouton "Cancel" qui ferme simplement la corbeille sans autres conséquences
	- l'appuie sur le bouton "Empty Trash" met à jours le booléen emptyTrashOrder, qui sera récupéré après
		par la fonction appelante qui pourra alors décider de vider la corbeille et donc de détruire physiquement
		toutes les notes contenues dedans.
	- le double-clickage sur une des notes provoque l'appel au NotesManager afin de récupérer l'instance de la note
		(grâce à son id contenue dans le \sa ListNoteViewItem ). Ainsi, une fois le dialog fermé, la fonction appelante
		pourra récuppérer cette note via la fonction getSelectedNote, si par contre le dialog a été quitté avec le cancel ou
		le empty trash, la valeur du pointeur de cette note sera NULL.

  \version	1.0
  \author	Florian Baune
*/
class TrashDialog : public QDialog
{
    Q_OBJECT

	public slots:
		void												setSelectedNote(QListWidgetItem* item);
		void												emptyTrash();

	public:
		// Constructor
		explicit TrashDialog(QWidget *parent = 0);

		// Getter
		Note*												getSelectedNote() const;
		bool												isEmpty() const;
		bool												isEmptyTrashOrder() const;
		const std::vector< pair <unsigned int, QString > >&	getTrashContent() const;

		// Destructor
		~TrashDialog();

	private:
		// Member
		Ui::TrashDialog*									ui;
		Note*												m_selectedNote;
		unsigned int										m_count;
		bool												m_emptyTrashOrder;
		std::vector< pair <unsigned int, QString > >		m_trash;
};

#endif // TRASHDIALOG_H
