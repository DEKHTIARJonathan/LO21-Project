#include "audioview.h"
#include "ui_audioview.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

AudioView::AudioView(Audio& a, QWidget *parent) :
	NoteView(parent),
	ui(new Ui::AudioView),
	m_aud(&a)
{
	ui->setupUi(this);

	// Setup
	QObject::connect(ui->searchAudio, SIGNAL(clicked()), this, SLOT(chooseAud()));
}

/********************************************************************
 *                           Slot Method		                    *
 ********************************************************************/

void AudioView::chooseAud(){
	QString fileName = QFileDialog::getOpenFileName(this, "Open Audio", QString(), "Audio File (*.*)");
	if(!fileName.isEmpty())
		loadAudioPath(fileName);
}

/********************************************************************
 *                              Method                              *
 ********************************************************************/

void AudioView::loadNoteContent(){
	ui->descEdit->setPlainText(m_aud->getDescription());
	loadAudioPath(m_aud->getPath());
}

void AudioView::setEditMode(bool b){
	ui->descEdit->setReadOnly(!b);
	ui->pathEdit->setReadOnly(!b);
	ui->searchAudio->setEnabled(b);
}

void AudioView::saveChanges(){
	m_aud->setPath(ui->pathEdit->text());
	m_aud->setDescription(ui->descEdit->toPlainText());
}

void AudioView::loadAudioPath(const QString& path){
	ui->pathEdit->setText(path);
}

/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

AudioView::~AudioView()
{
	delete ui;
}
