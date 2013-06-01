#ifndef AUDIO_H
#define AUDIO_H

#include <note/multimedia.h>

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
