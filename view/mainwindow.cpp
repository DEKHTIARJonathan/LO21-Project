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
	QObject::connect(ui->trashButton, SIGNAL(clicked()), this, SLOT(openTrash()));

	setAllIcons();
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

void MainWindow::newNote(){
	try{

		QAction* a = dynamic_cast<QAction*> (QObject::sender());
		if(a!=NULL)
			editNewNote(a->text());
		searchNotes();

	}
	catch(std::exception& e){
		showErrorMessageBox(QString(e.what()));
	}
}

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
	catch(std::exception& e){
		showErrorMessageBox(QString(e.what()));
	}
}

void MainWindow::deleteCancelNote(){
	try{

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
	catch(std::exception& e){
		showErrorMessageBox(QString(e.what()));
	}
}

void MainWindow::tagNote(){
	try{

		TagsDialog td(*m_actualNote);
		td.setModal(true);
		td.exec();

		if( !td.isCancelled() ){
			qDebug() << "Saving";
			DatabaseManager& db = DatabaseManager::getInstance();
			db.flushNoteAssoc(*m_actualNote);
			db.tagAssocNote(*m_actualNote, td.getSelectedTags());
		}

	}
	catch(std::exception& e){
		showErrorMessageBox(QString(e.what()));
	}
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

void MainWindow::changeWorkspace(){
	try{

		// Look for Path
		DatabaseManager& db = DatabaseManager::getInstance();

		// Show Worspace form
		WorkspaceForm w(db.getpath());
		w.setModal(true);
		w.exec();

		if( !w.isCanceled() && w.getPath() != db.getpath() ){
			GeneralViewFactory::getInstance().flushViews();
			NotesManager::getInstance().flush();
			DatabaseManager::destroy();
			DatabaseManager::getInstance(w.getPath());
			showEditor(false);
			clearListView();
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

void MainWindow::setAllIcons()
{
	QPixmap icnNew(":/icn/new");
	QPixmap icnOpen(":/icn/open");
	QPixmap icnQuit(":/icn/quit");
	QPixmap icnArticle(":/icn/article");
	QPixmap icnDocument(":/icn/document");
	QPixmap icnImage(":/icn/image");
	QPixmap icnVideo(":/icn/video");
	QPixmap icnAudio(":/icn/audio");
	QPixmap icnExport(":/icn/export");
	QPixmap icnTrash(":/icn/empty");

	// **************** Trash Icon ************************
	ui->trashButton->setFlat(true); // Pour enlever les bords
	ui->trashButton->setFocusPolicy(Qt::NoFocus); // Pour éviter d'avoir l'indication de focus sur l'image (pointillés)
	ui->trashButton->setIcon(icnTrash);
	ui->trashButton->setIconSize(QSize(128,128));
	ui->trashButton->setToolTip("Open the Trash");

	// ****************  New Project Button ***************

	ui->new_project->setFlat(true); // Pour enlever les bords
	ui->new_project->setFocusPolicy(Qt::NoFocus); // Pour éviter d'avoir l'indication de focus sur l'image (pointillés)
	ui->new_project->setIcon(icnNew);
	ui->new_project->setIconSize(QSize(25,25));
	ui->new_project->setToolTip("New Project");
	//connect(ui->new_project, SIGNAL(clicked()),...);

	// ****************  Open Project Button ***************

	ui->open_project->setFlat(true); // Pour enlever les bords
	ui->open_project->setFocusPolicy(Qt::NoFocus); // Pour éviter d'avoir l'indication de focus sur l'image (pointillés)
	ui->open_project->setIcon(icnOpen);
	ui->open_project->setIconSize(QSize(25,25));
	ui->open_project->setToolTip("Open Project");
	connect(ui->open_project, SIGNAL(clicked()), this, SLOT(changeWorkspace()));

	// ****************  Quit Button ***************

	ui->quit->setFlat(true); // Pour enlever les bords
	ui->quit->setFocusPolicy(Qt::NoFocus); // Pour éviter d'avoir l'indication de focus sur l'image (pointillés)
	ui->quit->setIcon(icnQuit);
	ui->quit->setIconSize(QSize(25,25));
	ui->quit->setToolTip("Close the Software");
	connect(ui->quit, SIGNAL(clicked()), this, SLOT(close()));

	// ****************  Export Button ***************

	ui->export_to_file->setFlat(true); // Pour enlever les bords
	ui->export_to_file->setFocusPolicy(Qt::NoFocus); // Pour éviter d'avoir l'indication de focus sur l'image (pointillés)
	ui->export_to_file->setIcon(icnExport);
	ui->export_to_file->setIconSize(QSize(25,25));
	ui->export_to_file->setToolTip("Export to File");
	//connect(ui->export_to_file, SIGNAL(clicked()), this, SLOT(close()));

	// ****************  New Article Button ***************

	ui->article->setFlat(true); // Pour enlever les bords
	ui->article->setFocusPolicy(Qt::NoFocus); // Pour éviter d'avoir l'indication de focus sur l'image (pointillés)
	ui->article->setIcon(icnArticle);
	ui->article->setIconSize(QSize(25,25));
	ui->article->setToolTip("Create a new Article");
	QAction* art = new QAction("Article", this);
	connect(ui->article, SIGNAL(clicked()), art, SLOT(trigger()));
	connect(art, SIGNAL(triggered()), this, SLOT(newNote()));

	// ****************  New Document Button ***************

	ui->document->setFlat(true); // Pour enlever les bords
	ui->document->setFocusPolicy(Qt::NoFocus); // Pour éviter d'avoir l'indication de focus sur l'image (pointillés)
	ui->document->setIcon(icnDocument);
	ui->document->setIconSize(QSize(25,25));
	ui->document->setToolTip("Create a new Document");
	QAction* doc = new QAction("Document", this);
	connect(ui->document, SIGNAL(clicked()), doc, SLOT(trigger()));
	connect(doc, SIGNAL(triggered()), this, SLOT(newNote()));

	// ****************  New Image Button ***************

	ui->image->setFlat(true); // Pour enlever les bords
	ui->image->setFocusPolicy(Qt::NoFocus); // Pour éviter d'avoir l'indication de focus sur l'image (pointillés)
	ui->image->setIcon(icnImage);
	ui->image->setIconSize(QSize(25,25));
	ui->image->setToolTip("Create a new Image");
	QAction* img = new QAction("Image", this);
	connect(ui->image, SIGNAL(clicked()), img, SLOT(trigger()));
	connect(img, SIGNAL(triggered()), this, SLOT(newNote()));

	// ****************  New Video Button ***************

	ui->video->setFlat(true); // Pour enlever les bords
	ui->video->setFocusPolicy(Qt::NoFocus); // Pour éviter d'avoir l'indication de focus sur l'image (pointillés)
	ui->video->setIcon(icnVideo);
	ui->video->setIconSize(QSize(25,25));
	ui->video->setToolTip("Create a new Video");
	QAction* vid = new QAction("Video", this);
	connect(ui->video, SIGNAL(clicked()), vid, SLOT(trigger()));
	connect(vid, SIGNAL(triggered()), this, SLOT(newNote()));

	// ****************  New Audio Button ***************

	ui->audio->setFlat(true); // Pour enlever les bords
	ui->audio->setFocusPolicy(Qt::NoFocus); // Pour éviter d'avoir l'indication de focus sur l'image (pointillés)
	ui->audio->setIcon(icnAudio);
	ui->audio->setIconSize(QSize(25,25));
	ui->audio->setToolTip("Create a new Audio");
	QAction* aud = new QAction("Audio", this);
	connect(ui->audio, SIGNAL(clicked()), aud, SLOT(trigger()));
	connect(aud, SIGNAL(triggered()), this, SLOT(newNote()));

}


/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

MainWindow::~MainWindow()
{
    delete ui;
}
