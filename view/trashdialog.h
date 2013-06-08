#ifndef TRASHDIALOG_H
#define TRASHDIALOG_H

#include <QDialog>

namespace Ui {
class TrashDialog;
}

class TrashDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit TrashDialog(QWidget *parent = 0);
    ~TrashDialog();
    
private:
    Ui::TrashDialog *ui;
};

#endif // TRASHDIALOG_H
