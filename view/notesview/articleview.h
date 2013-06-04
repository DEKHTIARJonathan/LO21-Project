#ifndef ARTICLEVIEW_H
#define ARTICLEVIEW_H

#include <QWidget>

#include <view/notesview/noteview.h>
#include <note/article.h>

namespace Ui {
	class ArticleView;
}

class ArticleView : public NoteView
{
		Q_OBJECT
		
	public slots:
		void				saveText();

	public:
		explicit ArticleView(Article &a, QWidget *parent = 0);
		~ArticleView();
		
	private:
		Ui::ArticleView*	ui;
		Article*			m_art;
};

#endif // ARTICLEVIEW_H
