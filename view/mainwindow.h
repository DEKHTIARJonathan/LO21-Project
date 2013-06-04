#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QtGui>
#include <QFileDialog>

#include <constants.h>
#include <notemanager/notesmanager.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
	public:
		// Constructor
		explicit MainWindow(QWidget *parent = 0);

		// Method
		void			displayNote( unsigned int id );

		// Destructor
		~MainWindow();
    
private:
	Ui::MainWindow*		ui;

	// Setup
	void				setupSearchArea();
	void				setupEditorArea();
	void				setupExportArea();
};

#endif // MAINWINDOW_H
