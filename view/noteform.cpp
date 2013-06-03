#include "noteform.h"
#include "ui_noteform.h"

NoteForm::NoteForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::NoteForm)
{
	ui->setupUi(this);
}

NoteForm::~NoteForm()
{
	delete ui;
}
