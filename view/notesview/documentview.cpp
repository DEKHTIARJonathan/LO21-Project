#include "documentview.h"
#include "ui_documentview.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

DocumentView::DocumentView(Document &a, QWidget *parent) :
	NoteView(parent),
	ui(new Ui::DocumentView),
	m_doc(&a)
{
	ui->setupUi(this);

	QObject::connect(ui->addNoteButton, SIGNAL(clicked()), this, SLOT(addNote()));
}

/********************************************************************
 *                           Slot Method		                    *
 ********************************************************************/

void DocumentView::addNote(){
	// Show Choose Note Dialog
	ChooseNoteDialog c;
	c.setModal(true);
	c.exec();

	if(c.getSelectedNote()!=NULL)
		addNoteDocumentView(*c.getSelectedNote(), true);
}

void DocumentView::showNoteOrder(){
	NoteDocumentView* v = dynamic_cast<NoteDocumentView*>( QObject::sender() );

	if( v!=NULL ){
		emit this->showNote(v->getNoteRef().getId());
	}
}

void DocumentView::removeNoteOrder(){
	NoteDocumentView* v = dynamic_cast<NoteDocumentView*>( QObject::sender() );

	if( v!=NULL ){
		removeNoteDocumentView(v);
	}
}

/********************************************************************
 *                              Method                              *
 ********************************************************************/

void DocumentView::loadNoteContent(){
	// Clear content
	clearViewList();

	// Load content
	for( std::vector<Note *>::iterator it = m_doc->begin(); it!=m_doc->end(); it++ ){
		addNoteDocumentView(**it);
	}
}

void DocumentView::setEditMode(bool b){
	ui->addNoteButton->setEnabled(b);
	emit editMode(b);
}

void DocumentView::saveChanges(){
	m_doc->flushNotes();
	const QObjectList& l = ui->noteArea->children();
	for( QObjectList::const_iterator it = l.begin(); it!=l.end(); it++ ){
		NoteDocumentView* v = dynamic_cast<NoteDocumentView*>( *it );

		if( v!=NULL )
			m_doc->addNote(v->getNoteRef());
	}
}

void DocumentView::addNoteDocumentView(Note& n, bool editMode){
	NoteDocumentView* v = new NoteDocumentView(n, ui->noteArea);
	QObject::connect(this, SIGNAL(editMode(bool)), v, SLOT(setEditMode(bool)));
	QObject::connect(v, SIGNAL(showNote()), this, SLOT(showNoteOrder()));
	QObject::connect(v, SIGNAL(removeNote()), this, SLOT(removeNoteOrder()));
	ui->noteLayout->insertWidget(ui->noteLayout->count()-1,v);
	v->setEditMode(editMode);
}

void DocumentView::removeNoteDocumentView(NoteDocumentView *v){
	ui->noteLayout->removeWidget(v);
	QObject::disconnect(this, SIGNAL(editMode(bool)), v, SLOT(setEditMode(bool)));
	QObject::disconnect(v, SIGNAL(showNote()), this, SLOT(showNoteOrder()));
	QObject::disconnect(v, SIGNAL(removeNote()), this, SLOT(removeNoteOrder()));
	v->setParent(NULL);
	delete v;
}

void DocumentView::clearViewList(){
	const QObjectList l = ui->noteArea->children();
	for( QObjectList::const_iterator it = l.begin(); it!=l.end(); it++ ){
		NoteDocumentView* v = dynamic_cast<NoteDocumentView*>( *it );

		if( v!=NULL )
			removeNoteDocumentView(v);
	}
}

/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

DocumentView::~DocumentView()
{
	clearViewList();
	delete ui;
}
