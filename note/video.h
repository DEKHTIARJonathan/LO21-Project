#ifndef VIDEO_H
#define VIDEO_H

#include <note/multimedia.h>

//! Vidéo
/*!
  Cette classe implémente simplement la classe Multimedia.
  Elle permet le stockage des imformations nécessaire à une Vidéo.

  \version	1.0
  \author	Florian Baune
*/
class Video : public MultiMedia
{
		Q_OBJECT

	public:
		// Constructor
		Video( unsigned int id );

	private:
		// Constructor
		Video( const Video& n);

		// Operator
		Video&		operator=(const Video& n);

};

#endif
