#ifndef INTERFACEEXPORTFACTORY_H
#define INTERFACEEXPORTFACTORY_H

#include <note/note.h>
#include <export/exportstrategy.h>

//! L'interface qui sera réimplémenté par la classe template ExportFactory.
/*!
  Cette interface fournit la méthode nécessaire à l'utilisation d'une Export Strategy.

  \version	1.0
  \author	Florian Baune & Jonathan Dekhtiar
*/
class InterfaceExportFactory
{
	public:
		//! Fonction virtuelle pure qui applique la stratégie d'export à une note donnée.
		/*!
		  \param	es		La stratégie d'export
		  \param	n		La note à exporter
		  \return	La QString résultat de l'export

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		virtual QString exportAsPart(ExportStrategy& es, const Note& n) = 0;
};

#endif // INTERFACEEXPORTFACTORY_H
