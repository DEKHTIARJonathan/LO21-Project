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
	QString			exportNote(const Note& n) const;
	QString			exportNote(const Article& a) const;
	QString			exportNote(const Document& d) const;
	QString			exportNote(const Image& i) const;
	QString			exportNote(const Video& v) const;
	QString			exportNote(const Audio& a) const;
	//static bool		exportFile(const QString &s, const QString &filename, const QString &exportPath);
	QString			escape(QString s) const;

};

#endif // EXPORTHTML_H
