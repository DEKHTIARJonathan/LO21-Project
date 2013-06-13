#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <vector>
#include <QDebug>

#include <note/note.h>
#include <note/documentindexoutofarrayexception.h>

using namespace std;

//! Document
/*!
  Cette classe implémente simplement la classe abstraite Note.
  Elle permet le stockage et la gestion d'un ensemble d'autres notes.

  \version	1.0
  \author	Florian Baune
*/
class Document : public Note
{
		Q_OBJECT

	public:
		// Constructor
		Document( unsigned int id );

		// Method
		//! Vérifie si une note (identifiée par son id) est présente dans le document.
		/*!
		  \param	id		L'id de la note.
		  \return	La réponse à la question, la note avec l'id \a id est-elle dans ce document ?

		  \version	1.0
		  \author	Florian Baune
		*/
		bool							containNote( unsigned int id ) const;

		//! Cette fonction ajoute une note à la fin du document.
		/*!
		  \param	n		La note que l'on souhaite ajouter.

		  \version	1.0
		  \author	Florian Baune
		*/
		void							addNote(Note &n);

		//! Retourne la Iième note de ce document.
		/*!
		  Si l'index de la note est incorrecte, cette fonction retourne une exception de type DocumentIndexOutOfArrayException.

		  \param	id		L'index de la note.
		  \return	La Iième note.

		  \version	1.0
		  \author	Florian Baune
		*/
		Note&							getNote(unsigned int i) const;

		//! Retire une note avec un id spécifique, ne faite rien si le document ne contient pas cette note.
		/*!
		  \param	id		L'id de la note.

		  \version	1.0
		  \author	Florian Baune
		*/
		void							removeNote(unsigned int id);

		//! Retire toutes les notes contenues dans ce document.
		/*!
		  \version	1.0
		  \author	Florian Baune
		*/
		void							flushNotes();

		//! Itérateur en tête positionné de liste.
		/*!
		  \return	L'itérateur positionné en tête de liste permettant de parcourir séquentiellement ce document.

		  \version	1.0
		  \author	Florian Baune
		*/
		vector<Note*>::iterator			begin();

		//! Itérateur Constant en tête positionné de liste.
		/*!
		  \return	L'itérateur Constant positionné en tête de liste permettant de parcourir séquentiellement ce document.

		  \version	1.0
		  \author	Florian Baune
		*/
		vector<Note*>::const_iterator	begin() const;

		//! Itérateur représentant la fin de liste.
		/*!
		  \return	L'itérateur représentant la fin de liste.
		  \version	1.0
		  \author	Florian Baune
		*/
		vector<Note*>::iterator			end();

		//! Itérateur Constant en tête positionné de liste.
		/*!
		  \return	L'itérateur Constant représentant la fin de liste.

		  \version	1.0
		  \author	Florian Baune
		*/
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
