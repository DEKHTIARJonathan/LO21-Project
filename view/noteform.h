#ifndef NOTEFORM_H
#define NOTEFORM_H

#include <QWidget>

namespace Ui {
	class NoteForm;
}

class NoteForm : public QWidget
{
		Q_OBJECT
		
	public:
		explicit NoteForm(QWidget *parent = 0);
		~NoteForm();
		
	private:
		Ui::NoteForm *ui;
};

#endif // NOTEFORM_H
