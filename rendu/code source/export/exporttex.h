#ifndef EXPORTTEX_H
#define EXPORTTEX_H

#include <QString>
#include <iostream>
#include <QStringBuilder>
#include "exportstrategy.h"

class ExportTex : public ExportStrategy
{
public:
    ExportTex();

	/*!
		 *  \brief renvoie une QString contenant le header d'un fichier tex
		 */
	QString			header() const;

	/*!
		 *  \brief renvoie une QString contenant le footer d'un fichier tex
		 */
	QString			footer() const;

	/*!
		 *  \brief renvoie une QString contenant le corps d'un article tex
		 */

	QString			exportNote(const Article& a) const;

	/*!
		 *  \brief renvoie une QString contenant le corps d'un document tex
		 */
	QString			exportNote(const Document& d) const;

	/*!
		 *  \brief renvoie une QString contenant le corps d'une image tex
		 */
	QString			exportNote(const Image& i) const;

	/*!
		 *  \brief renvoie une QString contenant le corps d'une video tex
		 */
	QString			exportNote(const Video& v) const;

	/*!
		 *  \brief renvoie une QString contenant le corps d'un video tex
		 */
	QString			exportNote(const Audio& a) const;

	/*!
		 *  \brief escape les caractères en relatif aux normes du TEX
		 */
	QString			escape(QString s) const;

private:
	/*!
		 *  \brief renvoie une QString contenant le corpscommun d'une note en TEX
		 */
	QString			exportNote(const Note& n) const;
};

#endif // EXPORTTEX_H
