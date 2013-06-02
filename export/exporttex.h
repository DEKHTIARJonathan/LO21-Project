#ifndef EXPORTTEX_H
#define EXPORTTEX_H

#include <QString>
#include <iostream>
#include <QStringBuilder>
#include "exportstrategy.h"

class ExportTex : public ExportStrategy
{
public:
    ExportTex();
	QString			header() const;
	QString			footer() const;
	QString			exportNote(const Note& n, unsigned int level = 0) const;
	QString			exportNote(const Article& a, unsigned int level = 0) const;
	QString			exportNote(const Document& d, unsigned int level = 0) const;
	QString			exportNote(const Image& i, unsigned int level = 0) const;
	QString			exportNote(const Video& v, unsigned int level = 0) const;
	QString			exportNote(const Audio& a, unsigned int level = 0) const;
	bool			exportFile(const QString &s, const QString &filename, const QString &exportPath) const;
	QString			escape(QString s) const;
};

#endif // EXPORTTEX_H
