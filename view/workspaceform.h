#ifndef WORKSPACEFORM_H
#define WORKSPACEFORM_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>

namespace Ui {
	class WorkspaceForm;
}

class WorkspaceForm : public QDialog
{
		Q_OBJECT
	public slots:
		void						cancel();
		void						loadPath(const QString &fileName);
		void						choosePath();
		void						createNewWorkSpace();
		
	public:
		// Constructor
		explicit WorkspaceForm(const QString &file, QWidget *parent = 0);

		// Getter
		bool						isCanceled() const;
		QString						getPath() const;

		// Destructor
		~WorkspaceForm();
		
	private:
		Ui::WorkspaceForm*			ui;
		QString						m_f;
		bool						m_canceled;
};

#endif // WORKSPACEFORM_H
