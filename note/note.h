#ifndef NOTE_H
#define NOTE_H

#include <QString>

class Note
{

	public:
		// Constructor
		Note( unsigned int id );
		Note( unsigned int id, const QString & name );

		// Getter
		unsigned int	getId() const;
		const QString &	getTitle() const;
		bool			isModified() const;

		// Setter
		void			setTitle( const QString & title);

		// Virtual Method

		// Method

	private:
		// Member
		unsigned int	m_id;
		QString			m_title;
		bool			m_modified;

};

#endif
