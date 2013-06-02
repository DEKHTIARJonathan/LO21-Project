#ifndef CONTAINERNOTEVIEW_H
#define CONTAINERNOTEVIEW_H

#include <QWidget>

namespace Ui {
class ContainerNoteView;
}

class ContainerNoteView : public QWidget
{
    Q_OBJECT
    
public:
    explicit ContainerNoteView(QWidget *parent = 0);
    ~ContainerNoteView();
    
private:
    Ui::ContainerNoteView *ui;
};

#endif // CONTAINERNOTEVIEW_H
