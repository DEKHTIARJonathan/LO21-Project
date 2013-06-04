#ifndef NOTEVIEW_H
#define NOTEVIEW_H

#include <QWidget>

class NoteView : public QWidget
{
		Q_OBJECT

	public:
		explicit NoteView(QWidget *parent = 0);
		
	signals:
		void	saveChanges();
	public slots:
		
};

#endif // NOTEVIEW_H
