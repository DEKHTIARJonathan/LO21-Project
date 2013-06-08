#ifndef DOCUMENTVIEW_H
#define DOCUMENTVIEW_H

#include <view/notesview/noteview.h>
#include <note/document.h>
#include <view/notesview/notedocumentview.h>
#include <view/notesview/choosenotedialog.h>

namespace Ui {
class DocumentView;
}

class DocumentView : public NoteView
{
		Q_OBJECT

	signals:
		void				editMode(bool b);

	public slots:
		void				addNote();
		void				showNoteOrder();
		void				removeNoteOrder();

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

		// Method
		void				addNoteDocumentView(Note& n);
		void				removeNoteDocumentView(NoteDocumentView* v);
};

#endif // DOCUMENTVIEW_H
