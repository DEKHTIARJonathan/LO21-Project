#include "mainwindow.h"
#include "ui_mainwindow.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow), m_actualNote(NULL), m_actualNoteView(NULL), m_editMode(false)
{
	ui->setupUi(this);

	// Setup MainView
	setupMenu();
	setupSearchArea();
	setupEditorArea();
	setupExportArea();

}

/********************************************************************
 *                              Setup                               *
 ********************************************************************/

void MainWindow::setupMenu(){

	// File Menu
	QObject::connect(ui->actionChange_WorkSpace, SIGNAL(triggered()), this, SLOT(changeWorkspace()));
	QObject::connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));

	// New Note Menu
	QList<QString> l = GeneralViewFactory::getInstance().getAvailableViewFactoryType();
	QList<QAction *> acts;

	for(QList<QString>::const_iterator it = l.begin(); it!=l.end(); it++){
		QAction* act = new QAction(*it, this);
		acts.append(act);
		QObject::connect(act, SIGNAL(triggered()), this, SLOT(newNote()));
	}

	ui->menuNewNote->addActions(acts);

}

void MainWindow::setupSearchArea(){
	// Connect
	QObject::connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(searchNotes()));
	QObject::connect(ui->noteList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(openNote(QListWidgetItem*)));
}

void MainWindow::setupEditorArea(){

	// Display
	showEditor(false);

	// Connects
	QObject::connect(ui->editSaveButton, SIGNAL(clicked()), this, SLOT(editSaveNote()));
	QObject::connect(ui->deleteCancelButton, SIGNAL(clicked()), this, SLOT(deleteCancelNote()));

	// Title
	ui->titleEdit->setMaxLength(constants::SIZE_MAX_TITLE);
}

void MainWindow::setupExportArea(){
	// Connects
	QObject::connect(ui->tabBox, SIGNAL(currentChanged(int)), this, SLOT(exportNote(int)));
}

/********************************************************************
 *                           Slot Method		                    *
 ********************************************************************/

void MainWindow::newNote(){
	QAction* a = static_cast<QAction*> (QObject::sender());
	if(a!=NULL)
		editNewNote(a->text());
}

void MainWindow::openNote(QListWidgetItem* i){
	ListNoteViewItem* item = static_cast<ListNoteViewItem*> (i);
	if( item!=NULL ){
		displayNote(item->getId());
	}
}

void MainWindow::editSaveNote(){
	if( !m_editMode ){
		// Setup Edit Mode
		ui->editSaveButton->setText("Save");
		ui->deleteCancelButton->setText("Cancel");
		ui->titleEdit->setReadOnly(false);
		m_actualNoteView->setEditMode(true);
	}
	else{
		// Save Note
		m_actualNote->setTitle(ui->titleEdit->text());
		m_actualNoteView->saveChanges();
		NotesManager::getInstance().saveNote(*m_actualNote);
		// And Setup View Mode
		m_actualNoteView->setEditMode(false);
		ui->titleEdit->setReadOnly(true);
		ui->deleteCancelButton->setText("Delete");
		ui->editSaveButton->setText("Edit");
	}
	m_editMode = !m_editMode;
}

void MainWindow::deleteCancelNote(){
	if( !m_editMode ){
		// To Do Delete
	}
	else{
		// Reload Original Note content and Setup View Mode
		loadActualNoteContent();
		m_actualNoteView->setEditMode(false);
		ui->titleEdit->setReadOnly(true);
		ui->deleteCancelButton->setText("Delete");
		ui->editSaveButton->setText("Edit");
		m_editMode = !m_editMode;
	}
}

void MainWindow::exportNote(int i){
	if( i!=0 ){
		if( m_editMode ){
			ui->tabBox->setCurrentIndex(0);
			showErrorMessageBox("Impossible to export note, currents modifications need to be saved before.");
		}
		else{
			// Get Export
			GeneralExportFactory& ef = GeneralExportFactory::getInstance();

			switch(i){
				case 1:
					ui->htmlArea->setHtml(ef.exportNote("html", *m_actualNote));
					break;
				case 2:
					ui->texArea->setText(ef.exportNote("tex", *m_actualNote));
					break;
				case 3:
					ui->txtArea->setText(ef.exportNote("txt", *m_actualNote));
					break;
				default:
					showErrorMessageBox("This box is not referenced in exportNote function.");
					break;
			}
		}
	}
}

void MainWindow::changeWorkspace(){
	// Look for Path
	DatabaseManager& db = DatabaseManager::getInstance();

	// Show Worspace form
	WorkspaceForm w(db.getpath());
	w.setModal(true);
	w.exec();

	if( !w.isCanceled() && w.getPath()!=db.getpath() ){
		showInfoMessageBox("Path Changed : "+w.getPath());
	}
}

void MainWindow::searchNotes(){
	// Get back search line's text
	QString search = ui->searchLine->text();

	// Start search in DataBase
	DatabaseManager& db = DatabaseManager::getInstance();
	std::vector< pair <unsigned int, QString > > result;
	if( search.isEmpty() )
		result = db.getNotes();
	else
		result = db.getNotes(search);

	// Clear List View
	QListWidget& l = *ui->noteList;
	QListWidgetItem* item = l.takeItem(0);
	while( item != NULL ){
		delete item;
		item = l.takeItem(0);
	}

	if(result.empty())
		// Show No Result Massage
		showInfoMessageBox("No result.");
	else{
		// Display results
		for( std::vector< pair <unsigned int, QString > >::const_iterator it = result.begin(); it!=result.end(); it++ )
			l.addItem( new ListNoteViewItem(it->first,it->second) );
		l.sortItems();
	}

}

/********************************************************************
 *                           Info Method		                    *
 ********************************************************************/

void MainWindow::showInfoMessageBox(const QString& msg){
	QMessageBox messageBox;
	messageBox.information(0,"Info",msg);
	messageBox.setFixedSize(500,200);
}

void MainWindow::showErrorMessageBox(const QString& msg){
	QMessageBox messageBox;
	messageBox.critical(0,"Error",msg);
	messageBox.setFixedSize(500,200);
}

/********************************************************************
 *                           Tool Method		                    *
 ********************************************************************/

void MainWindow::editNewNote( const QString& typeNote ){
	if( m_editMode )
		showErrorMessageBox("Impossible to edit new note, currents modifications need to be saved before.");
	else{
		// Create Note
		NotesManager& nm = NotesManager::getInstance();
		Note& n = nm.getNewNote(typeNote);

		// Display Note View
		displayNote(n);
	}
}

void MainWindow::displayNote( unsigned int id ){
	if( m_editMode )
		showErrorMessageBox("Impossible to open Note, currents modifications need to be saved before.");
	else{
		// Load Note
		NotesManager& nm = NotesManager::getInstance();
		Note& n = nm.getNote(id);

		// Display Note View
		displayNote(n);
	}
}

void MainWindow::displayNote(Note &n){
	if( m_editMode )
		showErrorMessageBox("Impossible to open Note, currents modifications need to be saved before.");
	else{
		// Clear Previous View
		clearActualNoteView();

		// Load Note View
		GeneralViewFactory& vf = GeneralViewFactory::getInstance();
		NoteView& nv = vf.getView(n);

		// Display Note View
		m_actualNote = &n;
		m_actualNoteView = &nv;
		nv.setParent(ui->speNoteArea);
		ui->speNoteLayout->addWidget(&nv);
		loadActualNoteContent();
		showEditor(true);
		ui->tabBox->setCurrentIndex(0);
	}
}

void MainWindow::clearActualNoteView(){
	if( m_actualNote != NULL ){
		// Hide Actual Note View
		showEditor(false);
		ui->speNoteLayout->removeWidget(m_actualNoteView);
		m_actualNoteView->setParent(NULL);
		m_actualNoteView = NULL;
		m_actualNote = NULL;
	}
}

void MainWindow::loadActualNoteContent(){
	if( m_actualNote != NULL ){
		// Load Actual Note in View
		ui->titleEdit->setText(m_actualNote->getTitle());
		m_actualNoteView->loadNoteContent();
	}
}

void MainWindow::showEditor(bool b){
	ui->tabBox->setEnabled(b);
	ui->editor->setVisible(b);
}

/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

MainWindow::~MainWindow()
{
    delete ui;
}
