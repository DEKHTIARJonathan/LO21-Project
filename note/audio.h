#ifndef AUDIO_H
#define AUDIO_H

#include <note/multimedia.h>

//! Audio
/*!
  Cette classe implémente simplement la classe Multimedia.
  Elle permet le stockage des imformations nécessaire à un Audio.

  \version	1.0
  \author	Florian Baune & Jonathan Dekhtiar
*/
class Audio : public MultiMedia
{
		Q_OBJECT

	public:
		// Constructor
		Audio( unsigned int id );

	private:
		// Constructor
		Audio( const Audio& n);

		// Operator
		Audio&		operator=(const Audio& n);

};

#endif
