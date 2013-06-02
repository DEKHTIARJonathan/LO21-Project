#ifndef EXPORTSTRATEGY_H
#define EXPORTSTRATEGY_H

#include <QHash>
#include <QFile>
#include <export/exportstrategynotfoundexception.h>
#include "note/classdef.h"
#include <note/note.h>

class ExportStrategy
{
	public:
		// Virtual Method
        virtual QString			header() const = 0 ;
        virtual QString			footer() const = 0 ;

		virtual QString			exportNote(const Article& n, unsigned int level = 0) const = 0 ;
		virtual QString			exportNote(const Document& n, unsigned int level = 0) const = 0 ;
		virtual QString			exportNote(const Image& n, unsigned int level = 0) const = 0 ;
		virtual QString			exportNote(const Audio& n, unsigned int level = 0) const = 0 ;
		virtual QString			exportNote(const Video& n, unsigned int level = 0) const = 0 ;
		virtual bool			exportFile(const QString &s, const QString &filename, const QString &exportPath) const = 0;

		virtual QString			escape(QString s) const = 0;

};

#endif
