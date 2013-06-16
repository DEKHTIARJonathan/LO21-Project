#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <QString>
#include <QFileInfo>
#include <note/note.h>

//! Article
/*!
  Cette classe implémente simplement la classe abstraite Note.
  Elle n'a pas vocation à être utilisé directement, mais réimplémenté par des types multimédias plus spécifique comme Image, Audio ou Video.

  \version	1.0
  \author	Florian Baune & Jonathan Dekhtiar
*/
class MultiMedia : public Note
{
		Q_OBJECT

	public:
		// Constructor
		MultiMedia( unsigned int id );

		// Getter
		const QString &	getDescription() const;
		const QString &	getPath() const;

		// Setter
		void			setDescription( const QString & description);
		void			setPath( const QString & path);
		void			binaryToWorkspace();

	private:
		// Constructor
		MultiMedia( const MultiMedia& n);

		// Member
		QString			m_description;
		QString			m_path;

		// Operator
		MultiMedia&		operator=(const MultiMedia& n);

};

#endif
