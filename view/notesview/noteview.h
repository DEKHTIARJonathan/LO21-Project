#ifndef NOTEVIEW_H
#define NOTEVIEW_H

#include <QWidget>

class NoteView : public QWidget
{
		Q_OBJECT

	signals:
		void				showNote(unsigned int id);

	public:
		// Constructor
		explicit NoteView(QWidget *parent = 0);

		// Method
		virtual void		loadNoteContent() = 0;
		virtual void		setEditMode(bool b) = 0;
		virtual void		saveChanges() = 0;

		// Destructor
		virtual ~NoteView();
};

#endif // NOTEVIEW_H
