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
}

/********************************************************************
 *                           Slot Method		                    *
 ********************************************************************/

void DocumentView::addNote(){
	// Show Choose Note Dialog
	ChooseNoteDialog c;
	c.setModal(true);
	c.exec();
}

void DocumentView::showNoteOrder(){
	NoteDocumentView* v = static_cast<NoteDocumentView*>( QObject::sender() );

	if( v!=NULL ){
		emit this->showNote(v->getNoteRef().getId());
	}
}

void DocumentView::removeNoteOrder(){
	NoteDocumentView* v = static_cast<NoteDocumentView*>( QObject::sender() );

	if( v!=NULL ){
		removeNoteDocumentView(v);
	}
}

/********************************************************************
 *                              Method                              *
 ********************************************************************/

void DocumentView::loadNoteContent(){
	for( std::vector<Note *>::iterator it = m_doc->begin(); it!=m_doc->end(); it++ ){
		addNoteDocumentView(**it);
	}
}

void DocumentView::setEditMode(bool b){
	emit editMode(b);
}

void DocumentView::saveChanges(){
	//m_doc->setText( ui->textEdit->toPlainText() );
}

void DocumentView::addNoteDocumentView(Note& n){
	NoteDocumentView* v = new NoteDocumentView(n, ui->noteArea);
	QObject::connect(this, SIGNAL(editMode(bool)), v, SLOT(setEditMode(bool)));
	QObject::connect(v, SIGNAL(showNote()), this, SLOT(displayNoteOrder()));
	QObject::connect(v, SIGNAL(removeNote()), this, SLOT(removeNoteOrder()));
	ui->noteLayout->addWidget(v);
}

void DocumentView::removeNoteDocumentView(NoteDocumentView *v){
	ui->noteLayout->removeWidget(v);
	QObject::disconnect(this, SIGNAL(editMode(bool)), v, SLOT(setEditMode(bool)));
	QObject::disconnect(v, SIGNAL(showNote()), this, SLOT(displayNoteOrder()));
	QObject::disconnect(v, SIGNAL(showNote()), this, SLOT(displayNoteOrder()));
	delete v;
}

/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

DocumentView::~DocumentView()
{
	delete ui;
}
