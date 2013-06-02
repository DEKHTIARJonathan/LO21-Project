#include "containernoteview.h"
#include "ui_containernoteview.h"

ContainerNoteView::ContainerNoteView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContainerNoteView)
{
    ui->setupUi(this);
}

ContainerNoteView::~ContainerNoteView()
{
    delete ui;
}
