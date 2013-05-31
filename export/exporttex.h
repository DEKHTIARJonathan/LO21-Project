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
	virtual QString			header() const;
	virtual QString			footer() const;
	virtual QString			exportNote(const Note& n, unsigned int level = 0) const;
};

#endif // EXPORTTEX_H
