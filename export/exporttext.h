#ifndef EXPORTTEXT_H
#define EXPORTTEXT_H

#include <QString>
#include <iostream>
#include "exportstrategy.h"

class ExportText : public ExportStrategy
{
public:
    ExportText();
	QString			header() const;
	QString			footer() const;
	QString			exportNote(const Note& n, unsigned int level = 0) const;
	QString			exportNote(const Article& a, unsigned int level = 0) const;
	QString			exportNote(const Document& d, unsigned int level = 0) const;
	QString			exportNote(const Image& i, unsigned int level = 0) const;
	QString			exportNote(const Video& v, unsigned int level = 0) const;
	QString			exportNote(const Audio& a, unsigned int level = 0) const;
	QString			escape(QString s) const;
};

#endif // EXPORTTEXT_H
