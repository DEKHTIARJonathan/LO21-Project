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
	QString			escape(QString s) const;
};

#endif // EXPORTTEXT_H
