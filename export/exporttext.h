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
	QString			exportNote(const Note& n) const;
	QString			exportNote(const Article& a) const;
	QString			exportNote(const Document& d) const;
	QString			exportNote(const Image& i) const;
	QString			exportNote(const Video& v) const;
	QString			exportNote(const Audio& a) const;
	QString			escape(QString s) const;
};

#endif // EXPORTTEXT_H
