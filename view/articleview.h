#ifndef ARTICLEVIEW_H
#define ARTICLEVIEW_H

#include <QWidget>

namespace Ui {
class ArticleView;
}

class ArticleView : public QWidget
{
    Q_OBJECT
    
public:
    explicit ArticleView(QWidget *parent = 0);
    ~ArticleView();
    
private:
    Ui::ArticleView *ui;
};

#endif // ARTICLEVIEW_H
