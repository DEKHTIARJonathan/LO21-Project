#ifndef NOTE_H
#define NOTE_H

#include <QString>

class Note
{

	public:
		// Constructor
		Note( unsigned int id, const QString & title, bool loaded, bool modified );

		// Getter
		unsigned int	getId() const;
		const QString &	getTitle() const;
		bool			getLoaded() const;
		bool			getModified() const;

		// Setter
		void			setTitle( const QString & title);

	private:
		// Member
		unsigned int	m_id;
		QString			m_title;
		bool			m_loaded;
		bool			m_modified;

};

#endif
