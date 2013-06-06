#ifndef INTERFACEEXPORTFACTORY_H
#define INTERFACEEXPORTFACTORY_H

#include <note/note.h>
#include <export/exportstrategy.h>

class InterfaceExportFactory
{
	public:
		virtual QString exportAsPart(ExportStrategy& es, const Note& n) = 0;
};

#endif // INTERFACEEXPORTFACTORY_H
