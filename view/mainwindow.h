#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QtGui>
#include <QFileDialog>

#include <constants.h>
#include <notemanager/notesmanager.h>
#include <view/notesview/generalviewfactory.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

	public slots:
		void				newNote();
		void				editSaveNote();
		void				deleteNote();
    
	public:
		// Constructor
		explicit MainWindow(QWidget *parent = 0);

		// Method
		void				editNewNote( const QString& NoteType );
		void				displayNote( unsigned int id );
		void				displayNote( Note& n );
		void				hideActualNote();

		// Destructor
		~MainWindow();
    
	private:
		// Member
		Ui::MainWindow*		ui;
		Note*				m_actualNote;
		NoteView*			m_actualNoteView;
		bool				m_editMode;

		// Method
		void				showErrorMessageBox(const QString& msg);
		void				enableNoteInterraction(bool b);

		// Setup
		void				setupMenu();
		void				setupSearchArea();
		void				setupEditorArea();
		void				setupExportArea();
};

#endif // MAINWINDOW_H
