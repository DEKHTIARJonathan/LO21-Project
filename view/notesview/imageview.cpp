#include "imageview.h"
#include "ui_imageview.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

ImageView::ImageView(Image& a, QWidget *parent) :
	NoteView(parent),
	ui(new Ui::ImageView),
	m_img(&a)
{
	ui->setupUi(this);

	// Setup
	QObject::connect(ui->searchImage, SIGNAL(clicked()), this, SLOT(chooseImg()));
}

/********************************************************************
 *                           Slot Method		                    *
 ********************************************************************/

void ImageView::chooseImg(){
	QString fileName = QFileDialog::getOpenFileName(this, "Open Image", QString(), "Img File (*.*)");
	if(!fileName.isEmpty())
		loadImagePath(fileName);
}

/********************************************************************
 *                              Method                              *
 ********************************************************************/

void ImageView::loadNoteContent(){
	ui->descEdit->setPlainText(m_img->getDescription());
	loadImagePath(m_img->getPath());
}

void ImageView::setEditMode(bool b){
	ui->descEdit->setReadOnly(!b);
	ui->searchImage->setEnabled(b);
}

void ImageView::saveChanges(){
	m_img->setPath(ui->pathEdit->text());
	m_img->setDescription(ui->descEdit->toPlainText());
}

void ImageView::loadImagePath(const QString& path){
	ui->pathEdit->setText(path);
	QPixmap img(path);
	ui->imageArea->setPixmap(img);
}

/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

ImageView::~ImageView()
{
	delete ui;
}
