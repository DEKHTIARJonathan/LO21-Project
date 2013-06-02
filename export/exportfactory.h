#ifndef EXPORTFACTORY_H
#define EXPORTFACTORY_H

#include <export/interfaceexportfactory.h>
#include <note/note.h>

template <class NoteType>
class ExportFactory : InterfaceExportFactory
{
	public:
		QString exportAsPart(ExportStrategy &es, const Note &n, unsigned int level){
			const NoteType& casted_n = dynamic_cast<const NoteType&> (n);
			return es(casted_n, level);
		}
};

#endif // EXPORTFACTORY_H
