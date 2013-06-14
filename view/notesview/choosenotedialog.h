#ifndef CHOOSENOTEDIALOG_H
#define CHOOSENOTEDIALOG_H

#include <QDialog>
#include <dbmanager/databasemanager.h>
#include <notemanager/notesmanager.h>
#include <view/listnoteviewitem.h>

namespace Ui {
	class ChooseNoteDialog;
}

//! Affiche une fenêtre permettant de choisir une nouvelle note à ajouter à un document
/*!

  \version	1.0
  \author	Florian Baune
*/
class ChooseNoteDialog : public QDialog
{
		Q_OBJECT
		
	public slots:
		//! Ce slot permet d'enregistrer la note qu'a séléctionné l'utilisateur.
		/*!
		  Ce slot sera directement connecté au signal itemDoubleClicked(QListWidgetItem*)

		  \version	1.0
		  \author	Florian Baune
		*/
		void							setSelectedNote(QListWidgetItem* item);

	public:
		explicit ChooseNoteDialog(const QList<unsigned int> &forbidIds, QWidget *parent = 0);
		Note*							getSelectedNote() const;
		~ChooseNoteDialog();
		
	private:
		Ui::ChooseNoteDialog *			ui;
		Note*							m_selectedNote;
};

#endif // CHOOSENOTEDIALOG_H
