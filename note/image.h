#ifndef IMAGE_H
#define IMAGE_H

#include <note/multimedia.h>

class Image : public MultiMedia
{

	public:
		// Constructor
		Image( unsigned int id );

	private:
		// Constructor
		Image( const Image& n);

		// Operator
		Image&		operator=(const Image& n);

};

#endif
