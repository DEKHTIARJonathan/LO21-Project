#ifndef VIDEO_H
#define VIDEO_H

#include <note/multimedia.h>

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
