#include "notedocumentview.h"
#include "ui_notedocumentview.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

NoteDocumentView::NoteDocumentView(Note &n, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::NoteDocumentView),
	m_noteRef(&n)
{
	ui->setupUi(this);

	// Setup
	QObject::connect(ui->showButton, SIGNAL(clicked()), this, SIGNAL(showNote()));
	QObject::connect(ui->removeButton, SIGNAL(clicked()), this, SIGNAL(removeNote()));

	ui->titleLabel->setText(QString() + "[" + n.metaObject()->className() + "] " + n.getTitle());
}

/********************************************************************
 *                              Getter                              *
 ********************************************************************/

Note&	NoteDocumentView::getNoteRef() const{	return *m_noteRef;	}

/********************************************************************
 *                           Slot Method		                    *
 ********************************************************************/

void NoteDocumentView::setEditMode(bool b){
	ui->showButton->setEnabled(!b);
	ui->removeButton->setEnabled(b);
}

/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

NoteDocumentView::~NoteDocumentView()
{
	delete ui;
}
