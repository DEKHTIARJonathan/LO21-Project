#ifndef ARTICLE_H
#define ARTICLE_H

#include <QString>

#include <note/note.h>
#include <note/strategies.h>

class Article : public Note, Strategies<Article>
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
