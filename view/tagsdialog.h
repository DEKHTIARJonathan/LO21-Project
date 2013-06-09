#ifndef TAGSDIALOG_H
#define TAGSDIALOG_H

#include <QDialog>
#include <QInputDialog>
#include <dbmanager/databasemanager.h>
#include <view/listnoteviewitem.h>

namespace Ui {
class TagsDialog;
}

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
		QStringList*								m_tagsList;
		QStringList									m_selectedTags;
};

#endif // TAGSDIALOG_H
