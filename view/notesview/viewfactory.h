#ifndef VIEWFACTORY_H
#define VIEWFACTORY_H

#include <view/notesview/interfaceviewfactory.h>

//! Classe template implémentant l'interface InterfaceViewFactory
/*!
  Cette classe factory template implémente la fabrication d'une vue du type passé en argument template, pour une note du type passé en argument template.

  \version	1.0
  \author	Florian Baune & Jonathan Dekhtiar
*/
template<class NoteType, class ViewType>
class ViewFactory : public InterfaceViewFactory
{
	public:
		//! Implémentation de la fonction exportAsPart de l'interface InterfaceExportFactory
		/*!
		  Si le type réel de la Note passée en paramère n'est pas celui du template,
		  cette fonction renvoie une CastException.

		  \param	n		La note à exporter
		  \return	La référence sur la vue nouvellement créée

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		NoteView& buildNoteView(Note& n){
			NoteType& casted_n = dynamic_cast<NoteType&> (n);

			return *( new ViewType(casted_n) );
		}
};

#endif // VIEWFACTORY_H
