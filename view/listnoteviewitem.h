#ifndef LISTNOTEVIEWITEM_H
#define LISTNOTEVIEWITEM_H

#include <QListWidgetItem>

class ListNoteViewItem : public QListWidgetItem
{

	public:
		// Constructor
		ListNoteViewItem( unsigned int id, const QString& title );

		// Getter
		unsigned int	getId() const;

	private:
		// Member
		unsigned int	m_id;

};

#endif
