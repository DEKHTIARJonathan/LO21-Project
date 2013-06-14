#ifndef DOCUMENTVIEW_H
#define DOCUMENTVIEW_H

#include <QDebug>

#include <view/notesview/noteview.h>
#include <note/document.h>
#include <view/notesview/notedocumentview.h>
#include <view/notesview/choosenotedialog.h>

namespace Ui {
class DocumentView;
}

//! L'implémentation de la vue pour un Document.
/*!
  Cette classe implémente les fonctionnalités de l'interface NoteView pour une note de type Document.

  \sa		NoteView

  \version	1.0
  \author	Florian Baune
*/
class DocumentView : public NoteView
{
		Q_OBJECT

	signals:
		void				editMode(bool b);

	public slots:
		//! Affiche la fenêtre de dialog ChooseNoteDialog permettant à l'utilisateur d'ajouter un document.
		/*!

		  \version	1.0
		  \author	Florian Baune
		*/
		void				addNote();

		//! Envoie l'ordre d'afficher une note à la fenêtre principale
		/*!
		  En réalité, ce slot récupère l'objet émetteur du signal qui a déclenché ce slot.
		  Et si cet émetteur est bien du type NoteDocumentView, alors il récupère l'id
		  lui étant attacher et envoie une demande d'affichage d'une note à la fenêtre principale
		  par le biai du signal showNote(unsigned int)

		  \sa NoteDocumentView

		  \version	1.0
		  \author	Florian Baune
		*/
		void				showNoteOrder();

		//! Retire l'objet NoteDocumentView qui a activé le slot.
		/*!

		  \version	1.0
		  \author	Florian Baune
		*/
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
		void				addNoteDocumentView(Note& n, bool editMode = false);
		void				removeNoteDocumentView(NoteDocumentView* v);
		void				clearViewList();
};

#endif // DOCUMENTVIEW_H
