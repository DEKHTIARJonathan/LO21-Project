#ifndef LISTNOTEVIEWITEM_H
#define LISTNOTEVIEWITEM_H

#include <QListWidgetItem>


//! Cette vue permet l'affichage et la gestion d'une description de note (son id et son titre)
/*!
  Cette classe est notamment utilisée dans les vues responsables de l'affichage d'une liste de notes.
  Par le biais de cette vue nous n'avons plus besoin d'instancier tout le contenue d'une note lorsqu'il
  ne s'agit que d'une recherche d'un ensemble de notes. Ensuite, lorsque par exemple l'utilisateur veut effectuer
  une action particulière sur la note comme l'affichage (dans la liste de recherche), la restauration (dans la corbeille)..
  il n'y a plus qu'à récupérer l'id contenue dans cette objet et accéder à la note complète via le NotesManager.

  \version	1.0
  \author	Florian Baune
*/
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
