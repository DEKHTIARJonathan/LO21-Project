#include "mainwindow.h"
#include "ui_mainwindow.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// Setup MainView
	setupSearchArea();
	setupEditorArea();
	setupExportArea();

}

/********************************************************************
 *                              Setup                               *
 ********************************************************************/

void MainWindow::setupSearchArea(){}

void MainWindow::setupEditorArea(){

	// Title
	ui->titleEdit->setMaxLength(constants::SIZE_MAX_TITLE);
}

void MainWindow::setupExportArea(){}

/********************************************************************
 *                         Controller Method                        *
 ********************************************************************/

void MainWindow::displayNote(unsigned int id){
	// Load Note
	NotesManager& nm = NotesManager::getInstance();
	Note& n = nm.getNote(id);

	// Load Note View
	// To DO
}

/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

MainWindow::~MainWindow()
{
    delete ui;
}
