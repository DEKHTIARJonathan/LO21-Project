#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QtGui>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <constants.h>
#include <notemanager/notesmanager.h>
#include <export/generalexportfactory.h>
#include <view/notesview/generalviewfactory.h>
#include <view/listnoteviewitem.h>
#include <view/workspaceform.h>
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
		void				newNote();
		void				openNote(QListWidgetItem* i);
		void				openNote(unsigned int id);
		void				editSaveNote();
		void				deleteCancelNote();
		void				searchNotes();
		void				exportNote(int i);
		void				changeWorkspace();
    
	public:
		// Constructor
		explicit MainWindow(QWidget *parent = 0);

		// Method
		void				editNewNote( const QString& NoteType );
		void				displayNote( unsigned int id );
		void				displayNote( Note& n );
		void				clearActualNoteView();

		// Destructor
		~MainWindow();
    
	private:
		// Member
		Ui::MainWindow*		ui;
		Note*				m_actualNote;
		NoteView*			m_actualNoteView;
		bool				m_editMode;

		// Method
		void				showInfoMessageBox(const QString& msg);
		void				showErrorMessageBox(const QString& msg);
		void				showEditor(bool b);
		void				loadActualNoteContent();

		// Setup
		void				setupMenu();
		void				setupSearchArea();
		void				setupEditorArea();
		void				setupExportArea();
};

#endif // MAINWINDOW_H
