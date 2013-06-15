#ifndef NOTE_H
#define NOTE_H

#include <QObject>
#include <QString>

//! Classe abstraite représentant une note générique avec un id et un titre.
/*!
  Cette classe abstraite hérite de QObject, ainsi, grâce au système de métaobjet de Qt, nous pourrons accéder
  dynamiquement au type de l'objet (sous la forme d'un QString). Cette fonctionnalité sera particulièrement pratique
  dans la fabrication/gestion des instances, dans les stratégies d'exports et dans la fabrication/gestion des vues.

  \version	1.0
  \author	Florian Baune & Jonathan Dekhtiar
*/
class Note : public QObject
{
		Q_OBJECT

	public:
		// Constructor
		//! Constructeur de base d'une note avec un id qui ne pourra plus être modifié par la suite.
		/*!
		  \param	id		L'id de la note.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		Note( unsigned int id );

		//! Constructeur de base d'une note avec un id qui ne pourra plus être modifié par la suite et un titre.
		/*!
		  \param	id		L'id de la note.
		  \param	name	Le titre de la note.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		Note( unsigned int id, const QString & name );

		// Getter
		unsigned int		getId() const;
		const QString &		getTitle() const;

		//! Getter permettant de savoir si la note a été modifié depuis ça dernière sauvegarde sur le support de sauvegarde.
		/*!
		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		bool				isModified() const;

		// Setter
		void				setTitle(const QString & title);

		// Operator
		bool				operator==(const Note& n) const;

		// Method
		//! Cette fonction reset le booléen de modification de la note. Ainsi, cette note sera considérée comme à jours par rapport au support de sauvegarde.
		/*!
		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				confirmSaving();

		// Destructor
		virtual ~Note();

	protected:
		bool				m_modified;	//!<	Le booléen de modification de la note, tant qu'il est faux, la note sera considérée comme à jours par rapport au support de sauvegarde.

	private:
		// Constructor
		Note( const Note& n);

		// Member
		const unsigned int	m_id;
		QString				m_title;

		// Operator
		Note&				operator=(const Note& n);

};

#endif
