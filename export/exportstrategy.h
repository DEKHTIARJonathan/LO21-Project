#ifndef EXPORTSTRATEGY_H
#define EXPORTSTRATEGY_H

#include <map>
#include <QString>

#include <note/note.h>
#include <export/exportstrategynotfoundexception.h>

using namespace std;

class ExportStrategy
{

	public:
		// Virtual Method
        virtual QString			header() const = 0 ;
        virtual QString			footer() const = 0 ;
		virtual QString			exportNote(const Note& n, unsigned int level = 0) const = 0 ;


		// Static Method
		static void				initExportStrategies();
		static ExportStrategy&	getExportStrategy(const QString& strategyName);

		// Static Attribut
		static map<QString,ExportStrategy*>	s_mapES;

};

#endif
