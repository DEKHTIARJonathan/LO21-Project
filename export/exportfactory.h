#ifndef EXPORTFACTORY_H
#define EXPORTFACTORY_H

#include <export/interfaceexportfactory.h>
#include <note/note.h>

template <class NoteType>
class ExportFactory : InterfaceExportFactory
{
	public:
		QString exportAsPart(ExportStrategy &es, const Note &n){
			const NoteType& casted_n = dynamic_cast<const NoteType&> (n);
			return es.exportNote(casted_n);
		}
};

#endif // EXPORTFACTORY_H
