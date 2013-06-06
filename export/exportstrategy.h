#ifndef EXPORTSTRATEGY_H
#define EXPORTSTRATEGY_H

#include <QHash>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <export/exportstrategynotfoundexception.h>
#include "note/classdef.h"
#include <note/note.h>

class ExportStrategy
{
	public:
		// Virtual Method
        virtual QString			header() const = 0 ;
        virtual QString			footer() const = 0 ;
		virtual QString			exportNote(const Note& n, unsigned int level = 0) const = 0 ;
		virtual QString			exportNote(const Article& a, unsigned int level = 0) const = 0 ;
		virtual QString			exportNote(const Document& d, unsigned int level = 0) const = 0 ;
		virtual QString			exportNote(const Image& i, unsigned int level = 0) const = 0 ;
		virtual QString			exportNote(const Audio& a, unsigned int level = 0) const = 0 ;
		virtual QString			exportNote(const Video& v, unsigned int level = 0) const = 0 ;
		static  bool			exportFile(const QString &s, const QString &filename, const QString & strategy, const QDir exportPath = QDir::current());
		virtual QString			escape(QString s) const = 0;

};

#endif
