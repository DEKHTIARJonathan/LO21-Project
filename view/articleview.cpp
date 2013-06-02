#include "articleview.h"
#include "ui_articleview.h"

ArticleView::ArticleView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArticleView)
{
    ui->setupUi(this);
}

ArticleView::~ArticleView()
{
    delete ui;
}
