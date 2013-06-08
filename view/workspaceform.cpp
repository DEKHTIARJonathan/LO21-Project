#include "workspaceform.h"
#include "ui_workspaceform.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

WorkspaceForm::WorkspaceForm(const QString& file, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::WorkspaceForm),
	m_f(),
	m_canceled(false)
{
	ui->setupUi(this);

	// Setup
	loadPath(file);
	QObject::connect(ui->choosePath, SIGNAL(clicked()), this, SLOT(choosePath()));
	QObject::connect(ui->newWorkSpaceButton, SIGNAL(clicked()), this, SLOT(createNewWorkSpace()));
	QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(close()));
	QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
}

/********************************************************************
 *                              Getter                              *
 ********************************************************************/

bool WorkspaceForm::isCanceled()const{	return m_canceled;	}
QString WorkspaceForm::getPath()const{	return m_f;			}

/********************************************************************
 *                           Slot Method		                    *
 ********************************************************************/

void WorkspaceForm::cancel(){
	m_canceled = true;
	this->close();
}

void WorkspaceForm::loadPath(const QString& fileName){
	m_f = fileName;
	ui->pathLine->setText(m_f);
}

void WorkspaceForm::choosePath(){
	QString fileName = QFileDialog::getOpenFileName(this, "Open DB", QString(), "DB File (*.lo21)");
	if(!fileName.isEmpty())
		loadPath(fileName);
}

void WorkspaceForm::createNewWorkSpace(){
	QString fileName = QFileDialog::getSaveFileName(this, "Create DB", QString(), "DB File (*.lo21)");
	if(!fileName.isEmpty())
		loadPath(fileName);
}

/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

WorkspaceForm::~WorkspaceForm()
{
	delete ui;
}
