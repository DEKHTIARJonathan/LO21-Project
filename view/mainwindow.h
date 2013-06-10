#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdexcept>
#include <QMainWindow>
#include <QApplication>
#include <QtGui>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QWebFrame>
#include <constants.h>
#include <notemanager/notesmanager.h>
#include <export/generalexportfactory.h>
#include <view/notesview/generalviewfactory.h>
#include <view/listnoteviewitem.h>
#include <view/workspaceform.h>
#include <view/trashdialog.h>
#include <view/tagsdialog.h>

#if QT_VERSION >= 0x050000 // Pour la version 5 et + il est nécessaire d'inclure QtWidgets
	#include <QtWidgets>
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

	public slots:
		// Note Management
		void				newArticle();
		void				newDocument();
		void				newImage();
		void				newAudio();
		void				newVideo();
		void				openNote(QListWidgetItem* i);
		void				openNote(unsigned int id);
		void				editSaveNote();
		void				deleteCancelNote();
		void				tagNote();
		// Export Management
		void				exportNoteAsHtml();
		void				exportNoteAsTeX();
		void				exportNoteAsTxt();
		void				exportNote(int i);
		void				exportNoteAsFile();
		// Search Management
		void				searchNotes();
		// Workspace Management
		void				createWorkspace();
		void				changeWorkspace();
		// Trash Management
		void				openTrash();
		void				emptyTrash();
    
	public:
		// Constructor
		explicit MainWindow(QWidget *parent = 0);

		// Destructor
		~MainWindow();
    
	private:
		// Member
		Ui::MainWindow*		ui;
		Note*				m_actualNote;
		NoteView*			m_actualNoteView;
		bool				m_editMode;

		// Info Method
		void				showInfoMessageBox(const QString& msg);
		void				showErrorMessageBox(const QString& msg);

		// Tool Method
		void				newNote(const QString &type);
		void				editNewNote( const QString& NoteType );
		void				displayNote( unsigned int id );
		void				displayNote( Note& n );
		void				clearActualNoteView();
		void				showEditor(bool b);
		void				loadActualNoteContent();
		void				clearListView();
		void				emptyTrash(const std::vector< pair <unsigned int, QString > >& trash);

		// Setup
		void				setupMenu();
		void				setupSearchArea();
		void				setupEditorArea();
		void				setupExportArea();

		// Icons
		void				setTrashIcon(bool empty = true);
		void				setAllIcons();
};

#endif // MAINWINDOW_H
