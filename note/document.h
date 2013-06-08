#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <vector>
#include <QDebug>

#include <note/note.h>
#include <note/documentindexoutofarrayexception.h>

using namespace std;

class Document : public Note
{
		Q_OBJECT

	public:
		// Constructor
		Document( unsigned int id );

		// Method
		bool							containNote( unsigned int id ) const;
		void							addNote(Note &n);
		Note&							getNote(unsigned int i) const;
		void							removeNote(unsigned int id);
		void							flushNotes();
		vector<Note*>::iterator			begin();
		vector<Note*>::const_iterator	begin() const;
		vector<Note*>::iterator			end();
		vector<Note*>::const_iterator	end() const;

	private:
		// Constructor
		Document( const Document& n);

		// Member
		vector<Note*>					m_notes;

		// Operator
		Document&						operator=(const Document& n);

};

#endif
