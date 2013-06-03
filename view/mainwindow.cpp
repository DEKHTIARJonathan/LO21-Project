#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //actionOuvrir
    //connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
    //QString s = QFileDialog::getOpenFileName(this, tr("Open Note Manager"), "/", tr("Note Manager File (*.lo21)"));

	NoteForm* c = new NoteForm(ui->Editor);
	ui->verticalLayout->addWidget(c);

}

MainWindow::~MainWindow()
{
    delete ui;
}
