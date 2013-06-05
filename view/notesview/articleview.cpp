#include "articleview.h"
#include "ui_articleview.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

ArticleView::ArticleView(Article &a, QWidget *parent) :
	NoteView(parent),
	ui(new Ui::ArticleView),
	m_art(&a)
{
	ui->setupUi(this);
	setEditMode(false);
}

/********************************************************************
 *                              Method                              *
 ********************************************************************/

void ArticleView::loadNoteContent(){
	ui->textEdit->setPlainText(m_art->getText());
}

void ArticleView::setEditMode(bool b){
	ui->textEdit->setReadOnly(!b);
}

void ArticleView::saveChanges(){
	m_art->setText( ui->textEdit->toPlainText() );
}

/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

ArticleView::~ArticleView()
{
	delete ui;
}
