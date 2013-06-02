#ifndef EXPORTSTRATEGY_H
#define EXPORTSTRATEGY_H

#include <QHash>

#include <export/exportstrategynotfoundexception.h>
#include <note/note.h>

class ExportStrategy
{

	public:
		// Virtual Method
        virtual QString			header() const = 0 ;
        virtual QString			footer() const = 0 ;
		virtual QString			exportNote(const Note& n, unsigned int level = 0) const = 0 ;
		virtual QString			escape(QString s) const = 0;

		//

		// Static Method
		static void						initExportStrategies();
		static ExportStrategy&			getExportStrategy(const QString& strategyName);

		// Static Attribut
		static QHash<QString,ExportStrategy*>	s_mapES;

};

#endif
