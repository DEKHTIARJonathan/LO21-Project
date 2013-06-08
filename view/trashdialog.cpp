#include "trashdialog.h"
#include "ui_trashdialog.h"

TrashDialog::TrashDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrashDialog)
{
    ui->setupUi(this);
}

TrashDialog::~TrashDialog()
{
    delete ui;
}
