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

	// Setup View
	QObject::connect(this, SIGNAL(saveChanges()), this, SLOT(saveText()));

}

/********************************************************************
 *                              Slots                               *
 ********************************************************************/

void ArticleView::saveText(){
	m_art->setText( ui->textEdit->toPlainText() );
}

/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

ArticleView::~ArticleView()
{
	delete ui;
}
