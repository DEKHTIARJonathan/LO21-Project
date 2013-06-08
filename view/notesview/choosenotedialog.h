#ifndef CHOOSENOTEDIALOG_H
#define CHOOSENOTEDIALOG_H

#include <QDialog>
#include <dbmanager/databasemanager.h>
#include <view/listnoteviewitem.h>

namespace Ui {
	class ChooseNoteDialog;
}

class ChooseNoteDialog : public QDialog
{
		Q_OBJECT
		
	public slots:
		void					setSelectedNote(Note& n);

	public:
		explicit ChooseNoteDialog(QWidget *parent = 0);
		Note&					getSelectedNote() const;
		~ChooseNoteDialog();
		
	private:
		Ui::ChooseNoteDialog *	ui;
		Note*					m_selectedNote;
};

#endif // CHOOSENOTEDIALOG_H