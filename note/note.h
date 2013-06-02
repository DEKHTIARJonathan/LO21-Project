#ifndef NOTE_H
#define NOTE_H

#include <QObject>
#include <QString>

class Note : public QObject
{
		Q_OBJECT

	public:
		// Constructor
		Note( unsigned int id );
		Note( unsigned int id, const QString & name );

		// Getter
		unsigned int		getId() const;
		const QString &		getTitle() const;
		bool				isModified() const;

		// Setter
		void				setTitle(const QString & title);

		// Operator
		bool				operator==(const Note& n) const;

		// Destructor
		virtual ~Note();

	private:
		// Constructor
		Note( const Note& n);

		// Member
		const unsigned int	m_id;
		QString				m_title;
		bool				m_modified;

		// Operator
		Note&				operator=(const Note& n);

};

#endif
