#ifndef ARTICLE_H
#define ARTICLE_H

#include <QString>

#include <note/note.h>

//! Article
/*!
  Cette classe implémente simplement la classe abstraite Note.
  Elle permet le stockage des imformations nécessaire à un Article.

  \version	1.0
  \author	Florian Baune
*/
class Article : public Note
{
		Q_OBJECT

	public:
		// Constructor
		Article( unsigned int id );

		// Getter
		const QString &	getText() const;

		// Setter
		void			setText( const QString & text);

	private:
		// Constructor
		Article( const Article& n);

		// Member
		QString			m_text;

		// Operator
		Article&		operator=(const Article& n);

};

#endif
