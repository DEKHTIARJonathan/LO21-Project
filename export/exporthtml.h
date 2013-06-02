#ifndef EXPORTHTML_H
#define EXPORTHTML_H

#include <QString>
#include <iostream>
#include "exportstrategy.h"

class ExportHTML : public ExportStrategy
{
public:
	ExportHTML();
	QString			header() const;
	QString			footer() const;
	QString			exportNote(const Note& n, unsigned int level = 0) const;
	QString			exportNote(const Article& a, unsigned int level = 0) const;
	QString			exportNote(const Document& d, unsigned int level = 0) const;
	QString			exportNote(const Image& i, unsigned int level = 0) const;
	QString			exportNote(const Video& v, unsigned int level = 0) const;
	QString			exportNote(const Audio& a, unsigned int level = 0) const;
	//static bool		exportFile(const QString &s, const QString &filename, const QString &exportPath);
	QString			escape(QString s) const;

};

#endif // EXPORTHTML_H
