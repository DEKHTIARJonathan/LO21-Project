#ifndef EXPORTSTRATEGY_H
#define EXPORTSTRATEGY_H

#include <export/exportstrategynotfoundexception.h>

class Note;
class Article;

class ExportStrategy
{

	public:
		// Virtual Method
        virtual QString			header() const = 0 ;
        virtual QString			footer() const = 0 ;
		virtual QString			exportNote(const Note& n, unsigned int level = 0) const = 0 ;
		virtual QString			exportNote(const Article& n, unsigned int level = 0) const = 0 ;
};

#endif
