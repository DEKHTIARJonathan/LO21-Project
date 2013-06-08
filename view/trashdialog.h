#ifndef TRASHDIALOG_H
#define TRASHDIALOG_H

#include <QDialog>
#include <dbmanager/databasemanager.h>
#include <notemanager/notesmanager.h>
#include <view/listnoteviewitem.h>

namespace Ui {
class TrashDialog;
}

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
