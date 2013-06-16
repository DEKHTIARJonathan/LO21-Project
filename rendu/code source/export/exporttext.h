#ifndef EXPORTTEXT_H
#define EXPORTTEXT_H

#include <QString>
#include <iostream>
#include "exportstrategy.h"

class ExportText : public ExportStrategy
{
public:
    ExportText();
	/*!
		 *  \brief renvoie une QString contenant le header d'un fichier texte
		 */
	QString			header() const;

	/*!
		 *  \brief renvoie une QString contenant le footer d'un fichier texte
		 */
	QString			footer() const;

	/*!
		 *  \brief renvoie une QString contenant le corps d'un article texte
		 */

	QString			exportNote(const Article& a) const;

	/*!
		 *  \brief renvoie une QString contenant le corps d'un document texte
		 */
	QString			exportNote(const Document& d) const;

	/*!
		 *  \brief renvoie une QString contenant le corps d'une image texte
		 */
	QString			exportNote(const Image& i) const;

	/*!
		 *  \brief renvoie une QString contenant le corps d'une video texte
		 */
	QString			exportNote(const Video& v) const;

	/*!
		 *  \brief renvoie une QString contenant le corps d'un video texte
		 */
	QString			exportNote(const Audio& a) const;

	/*!
		 *  \brief escape les caractères en relatif aux normes du texte
		 */
	QString			escape(QString s) const;

private:
	/*!
		 *  \brief renvoie une QString contenant le corpscommun d'une note en texte
		 */
	QString			exportNote(const Note& n) const;
};

#endif // EXPORTTEXT_H
