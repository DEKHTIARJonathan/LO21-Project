#ifndef ARTICLEVIEW_H
#define ARTICLEVIEW_H

#include <view/notesview/noteview.h>
#include <note/article.h>

namespace Ui {
	class ArticleView;
}

//! L'implémentation de la vue pour un Article.
/*!
  Cette classe implémente les fonctionnalités de l'interface NoteView pour une note de type Article.

  \sa		NoteView

  \version	1.0
  \author	Florian Baune & Jonathan Dekhtiar
*/
class ArticleView : public NoteView
{
		Q_OBJECT

	public:
		// Constructor
		explicit ArticleView(Article &a, QWidget *parent = 0);

		// Method
		void				loadNoteContent();
		void				setEditMode(bool b);
		void				saveChanges();

		// Destructor
		~ArticleView();
		
	private:
		Ui::ArticleView*	ui;
		Article*			m_art;
};

#endif // ARTICLEVIEW_H
