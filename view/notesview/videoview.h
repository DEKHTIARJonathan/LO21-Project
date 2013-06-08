#ifndef VIDEOVIEW_H
#define VIDEOVIEW_H

#include <QFileDialog>

#include <view/notesview/noteview.h>
#include <note/video.h>

namespace Ui {
	class VideoView;
}

class VideoView : public NoteView
{
        Q_OBJECT

    public slots:
        void						chooseAud();

    public:
        // Constructor
        explicit VideoView(Video& i, QWidget *parent = 0);

        // Method
        void						loadNoteContent();
        void						setEditMode(bool b);
        void						saveChanges();

        // Destructor
        ~VideoView();

    private:
        Ui::VideoView*				ui;
        Video*						m_vid;

        // Method
        void						loadVideoPath(const QString& path);
};

#endif // VIDEOVIEW_H
