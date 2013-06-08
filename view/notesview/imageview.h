#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QFileDialog>

#include <view/notesview/noteview.h>
#include <note/image.h>

namespace Ui {
	class ImageView;
}

class ImageView : public NoteView
{
		Q_OBJECT

	public slots:
		void				chooseImg();
		
	public:
		// Constructor
		explicit ImageView(Image& i, QWidget *parent = 0);

		// Method
		void				loadNoteContent();
		void				setEditMode(bool b);
		void				saveChanges();

		// Destructor
		~ImageView();
		
	private:
		Ui::ImageView*	ui;
		Image*			m_img;

		// Method
		void			loadImagePath(const QString& path);
};

#endif // IMAGEVIEW_H
