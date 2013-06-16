#ifndef EXPORTHTML_H
#define EXPORTHTML_H

#include <QString>
#include <iostream>
#include "exportstrategy.h"

class ExportHTML : public ExportStrategy
{
public:
	ExportHTML();
	/*!
		 *  \brief renvoie une QString contenant le header d'un fichier html
		 */
	QString			header() const;

	/*!
		 *  \brief renvoie une QString contenant le footer d'un fichier html
		 */
	QString			footer() const;

	/*!
		 *  \brief renvoie une QString contenant le corps d'un article html
		 */

	QString			exportNote(const Article& a) const;

	/*!
		 *  \brief renvoie une QString contenant le corps d'un document html
		 */
	QString			exportNote(const Document& d) const;

	/*!
		 *  \brief renvoie une QString contenant le corps d'une image html
		 */
	QString			exportNote(const Image& i) const;

	/*!
		 *  \brief renvoie une QString contenant le corps d'une video html
		 */
	QString			exportNote(const Video& v) const;

	/*!
		 *  \brief renvoie une QString contenant le corps d'un video html
		 */
	QString			exportNote(const Audio& a) const;

	/*!
		 *  \brief escape les caractères en relatif aux normes du HTML
		 */
	QString			escape(QString s) const;

private:
	/*!
		 *  \brief renvoie une QString contenant le corpscommun d'une note en HTML
		 */
	QString			exportNote(const Note& n) const;

};

#endif // EXPORTHTML_H
