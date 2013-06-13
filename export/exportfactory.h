#ifndef EXPORTFACTORY_H
#define EXPORTFACTORY_H

#include <export/interfaceexportfactory.h>
#include <note/note.h>

//! Classe template implémentant l'interface InterfaceExportFactory
/*!
  Cette classe factory template implémente l'export d'une note du type passé en argument template.

  \version	1.0
  \author	Florian Baune
*/
template <class NoteType>
class ExportFactory : InterfaceExportFactory
{
	public:
		//! Implémentation de la fonction exportAsPart de l'interface InterfaceExportFactory
		/*!
		  Si le type réel de la Note passée en paramère n'est pas celui du template,
		  cette fonction renvoie une CastException.

		  \param	es		La stratégie d'export
		  \param	n		La note à exporter
		  \return	La QString résultat de l'export

		  \version	1.0
		  \author	Florian Baune
		*/
		QString exportAsPart(ExportStrategy &es, const Note &n){
			const NoteType& casted_n = dynamic_cast<const NoteType&> (n);
			return es.exportNote(casted_n);
		}
};

#endif // EXPORTFACTORY_H
