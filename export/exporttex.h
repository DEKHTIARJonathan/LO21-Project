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
	QString			escape(QString s) const;
};

#endif // EXPORTTEX_H
