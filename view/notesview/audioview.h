#ifndef AUDIOVIEW_H
#define AUDIOVIEW_H

#include <QFileDialog>

#include <view/notesview/noteview.h>
#include <note/audio.h>

namespace Ui {
	class AudioView;
}

//! L'implémentation de la vue pour un Audio.
/*!
  Cette classe implémente les fonctionnalités de l'interface NoteView pour une note de type Audio.

  \sa		NoteView

  \version	1.0
  \author	Florian Baune & Jonathan Dekhtiar
*/
class AudioView : public NoteView
{
		Q_OBJECT

	public slots:
		void						chooseAud();

	public:
		// Constructor
		explicit AudioView(Audio& i, QWidget *parent = 0);

		// Method
		void						loadNoteContent();
		void						setEditMode(bool b);
		void						saveChanges();

		// Destructor
        ~AudioView();

	private:
		Ui::AudioView*				ui;
		Audio*						m_aud;

		// Method
		void						loadAudioPath(const QString& path);
};

#endif // AUDIOVIEW_H
