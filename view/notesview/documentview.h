#ifndef DOCUMENTVIEW_H
#define DOCUMENTVIEW_H

#include <view/notesview/noteview.h>
#include <note/document.h>
#include <view/notesview/notedocumentview.h>

namespace Ui {
class DocumentView;
}

class DocumentView : public NoteView
{
		Q_OBJECT

	public:
		// Constructor
		explicit DocumentView(Document &a, QWidget *parent = 0);

		// Method
		void				loadNoteContent();
		void				setEditMode(bool b);
		void				saveChanges();

		// Destructor
		~DocumentView();

	private:
		Ui::DocumentView*	ui;
		Document*			m_doc;
};

#endif // DOCUMENTVIEW_H
