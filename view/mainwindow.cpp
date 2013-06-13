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

	// Display all notes
	searchNotes();

	// Display Trash
	setTrashIcon(DatabaseManager::getInstance().isTrashEmpty());

}

/********************************************************************
 *                              Setup                               *
 ********************************************************************/

void MainWindow::setupMenu(){

	// File Menu
		// New Note Menu
		QObject::connect(ui->actionNew_Article, SIGNAL(triggered()), this, SLOT(newArticle()));
		QObject::connect(ui->actionNew_Document, SIGNAL(triggered()), this, SLOT(newDocument()));
		QObject::connect(ui->actionNew_Image, SIGNAL(triggered()), this, SLOT(newImage()));
		QObject::connect(ui->actionNew_Audio, SIGNAL(triggered()), this, SLOT(newAudio()));
		QObject::connect(ui->actionNew_Video, SIGNAL(triggered()), this, SLOT(newVideo()));

	QObject::connect(ui->actionOpenTrash, SIGNAL(triggered()), this, SLOT(openTrash()));
	QObject::connect(ui->actionCreate_WorkSpace, SIGNAL(triggered()), this, SLOT(createWorkspace()));
	QObject::connect(ui->actionChange_WorkSpace, SIGNAL(triggered()), this, SLOT(changeWorkspace()));
	QObject::connect(ui->actionExport_As_File, SIGNAL(triggered()), this, SLOT(exportNoteAsFile()));
	QObject::connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));

	// EditMenu
	QObject::connect(ui->actionTags, SIGNAL(triggered()), this, SLOT(tagNote()));
	QObject::connect(ui->actionEdit, SIGNAL(triggered()), this, SLOT(editSaveNote()));
	QObject::connect(ui->actionDelete, SIGNAL(triggered()), this, SLOT(deleteCancelNote()));
	QObject::connect(ui->actionCopy_Binaries, SIGNAL(triggered()), this, SLOT(copyBinaries()));
	QObject::connect(ui->actionHtml, SIGNAL(triggered()), this, SLOT(exportNoteAsHtml()));
	QObject::connect(ui->actionTeX, SIGNAL(triggered()), this, SLOT(exportNoteAsTeX()));
	QObject::connect(ui->actionTxt, SIGNAL(triggered()), this, SLOT(exportNoteAsTxt()));

}

void MainWindow::setupSearchArea(){
	// Connect
	QObject::connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(searchNotes()));
	QObject::connect(ui->noteList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(openNote(QListWidgetItem*)));
	QObject::connect(ui->trashButton, SIGNAL(clicked()), this, SLOT(openTrash()));
}

void MainWindow::setupEditorArea(){

	// Display
	showEditor(false);

	// Connects
	QObject::connect(ui->tagButton, SIGNAL(clicked()), this, SLOT(tagNote()));
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

void MainWindow::newArticle()	{ newNote(Article::staticMetaObject.className());	}
void MainWindow::newDocument()	{ newNote(Document::staticMetaObject.className());	}
void MainWindow::newImage()		{ newNote(Image::staticMetaObject.className());     }
void MainWindow::newAudio()		{ newNote(Audio::staticMetaObject.className());     }
void MainWindow::newVideo()		{ newNote(Video::staticMetaObject.className());     }

void MainWindow::openNote(QListWidgetItem* i){
	try{

		ListNoteViewItem* item = dynamic_cast<ListNoteViewItem*> (i);
		if( item!=NULL ){
			displayNote(item->getId());
		}

	}
	catch(std::exception& e){
		showErrorMessageBox(QString(e.what()));
	}
}

void MainWindow::openNote(unsigned int id){
	try{

		displayNote(id);

	}
	catch(std::exception& e){
		showErrorMessageBox(QString(e.what()));
	}
}

void MainWindow::editSaveNote(){
	try{

		if(m_actualNote!=NULL){
			if( !m_editMode ){
				// Setup Edit Mode
				ui->editSaveButton->setText("Save");
				ui->deleteCancelButton->setText("Cancel");
				ui->titleEdit->setReadOnly(false);
				m_actualNoteView->setEditMode(true);
			}
			else{
				// Save Note
				bool titleChanged = m_actualNote->getTitle() != ui->titleEdit->text();
				if( titleChanged )
					m_actualNote->setTitle(ui->titleEdit->text());
				m_actualNoteView->saveChanges();
				NotesManager::getInstance().saveNote(*m_actualNote);
				if( titleChanged )
					searchNotes();
				// And Setup View Mode
				m_actualNoteView->setEditMode(false);
				ui->titleEdit->setReadOnly(true);
				ui->deleteCancelButton->setText("Put to Trash");
				ui->editSaveButton->setText("Edit");
			}
			m_editMode = !m_editMode;
		}

	}
	catch(std::exception& e){
		showErrorMessageBox(QString(e.what()));
	}
}

void MainWindow::deleteCancelNote(){
	try{

		if(m_actualNote!=NULL){
			if( !m_editMode ){
				// Delete Note
				NotesManager::getInstance().putToTrash(*m_actualNote);
				clearActualNoteView();
				searchNotes();

				// Update Trash Icon
				setTrashIcon(false);
			}
			else{
				// Reload Original Note content and Setup View Mode
				loadActualNoteContent();
				m_actualNoteView->setEditMode(false);
				ui->titleEdit->setReadOnly(true);
				ui->deleteCancelButton->setText("Put to Trash");
				ui->editSaveButton->setText("Edit");
				m_editMode = !m_editMode;
			}
		}

	}
	catch(std::exception& e){
		showErrorMessageBox(QString(e.what()));
	}
}

void MainWindow::tagNote(){
	try{

		if(m_actualNote!=NULL){
			TagsDialog td(*m_actualNote);
			td.setModal(true);
			td.exec();

			if( !td.isCancelled() ){
				DatabaseManager& db = DatabaseManager::getInstance();
				db.flushNoteAssoc(*m_actualNote);
				db.tagAssocNote(*m_actualNote, td.getSelectedTags());
			}
		}

	}
	catch(std::exception& e){
		showErrorMessageBox(QString(e.what()));
	}
}

void MainWindow::exportNoteAsHtml(){
	if( !m_editMode && m_actualNote!=NULL )
		ui->tabBox->setCurrentIndex(1);
}

void MainWindow::exportNoteAsTeX(){
	if( !m_editMode && m_actualNote!=NULL )
		ui->tabBox->setCurrentIndex(2);
}

void MainWindow::exportNoteAsTxt(){
	if( !m_editMode && m_actualNote!=NULL )
		ui->tabBox->setCurrentIndex(3);
}

void MainWindow::exportNote(int i){
	try{

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
	catch(std::exception& e){
		showErrorMessageBox(QString(e.what()));
	}
}

void MainWindow::exportNoteAsFile(){
	try{

		int i = ui->tabBox->currentIndex();

		if( i!=0 ){
			if( m_editMode ){
				ui->tabBox->setCurrentIndex(0);
				showErrorMessageBox("Impossible to export note, currents modifications need to be saved before.");
			}
			else{
				// Get Export
				QString fileName;

				switch(i){
					case 1:
						fileName = QFileDialog::getSaveFileName(this, "Export Html File", QString(), "DB File (*.html)");
						if(!fileName.isEmpty())
							ExportStrategy::exportFile(ui->htmlArea->page()->mainFrame()->toHtml(), fileName);
						break;
					case 2:
						fileName = QFileDialog::getSaveFileName(this, "Export TeX File", QString(), "DB File (*.tex)");
						if(!fileName.isEmpty())
							ExportStrategy::exportFile(ui->texArea->toPlainText(), fileName);
						break;
					case 3:
						fileName = QFileDialog::getSaveFileName(this, "Export Txt File", QString(), "DB File (*.txt)");
						if(!fileName.isEmpty())
							ExportStrategy::exportFile(ui->txtArea->toPlainText(), fileName);
						break;
					default:
						showErrorMessageBox("This box is not referenced in exportNote function.");
						break;
				}
			}
		}

	}
	catch(std::exception& e){
		showErrorMessageBox(QString(e.what()));
	}
}

void MainWindow::createWorkspace(){
	try{

		// Look new Path
		DatabaseManager& db = DatabaseManager::getInstance();
		QString fileName = QFileDialog::getSaveFileName(this, "Create DB", QString(), "DB File (*.lo21)");

		if( !fileName.isEmpty() && fileName != db.getpath() ){
			clearActualNoteView();
			GeneralViewFactory::getInstance().flushViews();
			NotesManager::getInstance().flush();
			DatabaseManager::destroy();
			DatabaseManager::getInstance(fileName);
			clearListView();
			setTrashIcon(true);
		}

	}
	catch(std::exception& e){
		showErrorMessageBox(QString(e.what()));
	}
}

void MainWindow::changeWorkspace(){
	try{

		// Look new Path
		DatabaseManager& db = DatabaseManager::getInstance();
		QString fileName = QFileDialog::getOpenFileName(this, "Open DB", db.getpath(), "DB File (*.lo21)");

		if( !fileName.isEmpty() && fileName != db.getpath() ){
			clearActualNoteView();
			GeneralViewFactory::getInstance().flushViews();
			NotesManager::getInstance().flush();
			DatabaseManager::destroy();
			DatabaseManager& newDb = DatabaseManager::getInstance(fileName);
			clearListView();
			searchNotes();
			setTrashIcon(newDb.isTrashEmpty());
		}

	}
	catch(std::exception& e){
		showErrorMessageBox(QString(e.what()));
	}
}

void MainWindow::searchNotes(){
	try{

		// Get back search line's text
		QString search = ui->searchLine->text();

		// Start search in DataBase
		DatabaseManager& db = DatabaseManager::getInstance();
		std::vector< pair <unsigned int, QString > > result;
		if( search.isEmpty() )
			result = db.getNotes();
		else
			result = db.getNotes(search);

		// Reference
		QListWidget& l = *ui->noteList;

		// Clear List View
		clearListView();

		if(!result.empty()){
			// Display results
			for( std::vector< pair <unsigned int, QString > >::const_iterator it = result.begin(); it!=result.end(); it++ )
				l.addItem( new ListNoteViewItem(it->first,it->second) );
			l.sortItems();
		}

	}
	catch(std::exception& e){
		showErrorMessageBox(QString(e.what()));
	}

}

void MainWindow::openTrash(){
	try{

		// Show Worspace form
		TrashDialog w;
		w.setModal(true);
		w.exec();

		// If a note was double-clicked, remove it from the trash and display it
		if( w.getSelectedNote() != NULL ){
			DatabaseManager::getInstance().removeFromTrash(w.getSelectedNote()->getId());
			displayNote(*w.getSelectedNote());
			searchNotes();

            // Update Trash Icon
            if(w.isEmpty())
                setTrashIcon();
		}

		// If empty trash order was sent
		if( w.isEmptyTrashOrder() ){
			emptyTrash(w.getTrashContent());
		}

	}
	catch(std::exception& e){
		showErrorMessageBox(QString(e.what()));
	}
}

void MainWindow::emptyTrash(){
	try{

		std::vector< pair <unsigned int, QString > > trash = DatabaseManager::getInstance().getTrash();
		emptyTrash(trash);

	}
	catch(std::exception& e){
		showErrorMessageBox(QString(e.what()));
	}
}

void MainWindow::copyBinaries(){
	try{

		if(m_actualNote!=NULL && !m_editMode){
			MultiMedia* m = dynamic_cast<MultiMedia*> ( m_actualNote );
			if( m==NULL )
				showInfoMessageBox("Actual note didn't content any binary linked files.");
			else{
				m->binaryToWorkspace();
				displayNote(*m);
				showInfoMessageBox("Binary Content had been saved in local folder.");
			}
		}

	}
	catch(std::exception& e){
		showErrorMessageBox(QString(e.what()));
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

void MainWindow::newNote(const QString& type){
	try{

		editNewNote(type);
		searchNotes();

	}
	catch(std::exception& e){
		showErrorMessageBox(QString(e.what()));
	}
}

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
		QObject::disconnect(m_actualNoteView, SIGNAL(showNote(uint)), this, SLOT(openNote(uint)));
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
		m_actualNoteView->setEditMode(false);
		QObject::connect(m_actualNoteView, SIGNAL(showNote(uint)), this, SLOT(openNote(uint)));
	}
}

void MainWindow::showEditor(bool b){
	ui->tabBox->setEnabled(b);
	ui->editor->setVisible(b);
}

void MainWindow::clearListView(){
	QListWidget& l = *ui->noteList;
	QListWidgetItem* item = l.takeItem(0);
	while( item != NULL ){
		delete item;
		item = l.takeItem(0);
	}
}

void MainWindow::emptyTrash(const std::vector< pair <unsigned int, QString > >& trash){
	// Delete view part of Notes in trash
	GeneralViewFactory& vf = GeneralViewFactory::getInstance();
	for(std::vector< pair <unsigned int, QString > >::const_iterator it = trash.begin(); it!=trash.end(); it++){
		vf.deleteView(it->first);
	}

	// Empty model part of Notes in trash
	NotesManager::getInstance().emptyTrash(trash);

    // Update Trash Icon
    setTrashIcon();
}

/********************************************************************
 *                              Icons                               *
 ********************************************************************/

void MainWindow::setTrashIcon(bool empty)
{
	QPixmap buttonImage;

	if(empty)
		buttonImage.load(":/icn/empty");
	else
		buttonImage.load(":/icn/full");

	QIcon Icon;
	Icon.addPixmap ( buttonImage, QIcon::Normal, QIcon::Off );
	ui->trashButton->setIcon(Icon);
	ui->trashButton->setIconSize(QSize(128,128));
}

/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

MainWindow::~MainWindow()
{
    delete ui;
}
