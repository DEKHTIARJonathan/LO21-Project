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
	setEditMode(false);
}

/********************************************************************
 *                              Method                              *
 ********************************************************************/

void DocumentView::loadNoteContent(){
	ui->textEdit->setPlainText(m_doc->getText());
}

void DocumentView::setEditMode(bool b){
	ui->textEdit->setReadOnly(!b);
}

void DocumentView::saveChanges(){
	m_doc->setText( ui->textEdit->toPlainText() );
}

/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

DocumentView::~DocumentView()
{
	delete ui;
}
