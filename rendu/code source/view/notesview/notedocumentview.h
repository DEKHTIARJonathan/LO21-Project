#ifndef NOTEDOCUMENTVIEW_H
#define NOTEDOCUMENTVIEW_H

#include <QWidget>
#include <note/note.h>


namespace Ui {
	class NoteDocumentView;
}

//! Cette petite interface permet de gérer les notes à l'intérieur de la vue d'un Document
/*!
  Cette interface permet gérer l'affichage de la note contenue dans le Document ainsi que ça suppression du Document.

  \version	1.0
  \author	Florian Baune & Jonathan Dekhtiar
*/
class NoteDocumentView : public QWidget
{
		Q_OBJECT
		
	signals:
		void					showNote();
		void					removeNote();

	public slots:
		void					setEditMode(bool b);

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
