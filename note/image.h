#ifndef IMAGE_H
#define IMAGE_H

#include <note/multimedia.h>

//! Image
/*!
  Cette classe implémente simplement la classe Multimedia.
  Elle permet le stockage des imformations nécessaire à une Image.

  \version	1.0
  \author	Florian Baune
*/
class Image : public MultiMedia
{
		Q_OBJECT

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
