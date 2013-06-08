#ifndef NOTEDOCUMENTVIEW_H
#define NOTEDOCUMENTVIEW_H

#include <QWidget>
#include <note/note.h>


namespace Ui {
	class NoteDocumentView;
}

class NoteDocumentView : public QWidget
{
		Q_OBJECT
		
	signals:
		void					showNote();
		void					removeNote();

	public:
		// Constructor
		explicit NoteDocumentView(Note& n, QWidget *parent = 0);

		// Getter
		Note&					getNoteRef() const;

		// Destructor
		~NoteDocumentView();
		
	private:
		Ui::NoteDocumentView*	ui;
		Note*					m_noteRef;
};

#endif // NOTEDOCUMENTVIEW_H
