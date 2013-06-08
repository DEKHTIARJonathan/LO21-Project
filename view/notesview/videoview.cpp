#include "videoview.h"
#include "ui_videoview.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

VideoView::VideoView(Video& a, QWidget *parent) :
	NoteView(parent),
	ui(new Ui::VideoView),
	m_vid(&a)
{
	ui->setupUi(this);

	// Setup
	QObject::connect(ui->searchVideo, SIGNAL(clicked()), this, SLOT(chooseAud()));
}

/********************************************************************
 *                           Slot Method		                    *
 ********************************************************************/

void VideoView::chooseAud(){
	QString fileName = QFileDialog::getOpenFileName(this, "Open Audio", QString(), "Audio File (*.*)");
	if(!fileName.isEmpty())
		loadVideoPath(fileName);
}

/********************************************************************
 *                              Method                              *
 ********************************************************************/

void VideoView::loadNoteContent(){
	ui->descEdit->setPlainText(m_vid->getDescription());
	loadVideoPath(m_vid->getPath());
}

void VideoView::setEditMode(bool b){
	ui->descEdit->setReadOnly(!b);
	ui->searchVideo->setEnabled(b);
}

void VideoView::saveChanges(){
	m_vid->setPath(ui->pathEdit->text());
	m_vid->setDescription(ui->descEdit->toPlainText());
}

void VideoView::loadVideoPath(const QString& path){
	ui->pathEdit->setText(path);
}

/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

VideoView::~VideoView()
{
	delete ui;
}

