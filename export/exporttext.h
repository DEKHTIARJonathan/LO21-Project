#ifndef EXPORTTEXT_H
#define EXPORTTEXT_H

#include <QString>
#include <iostream>
#include "exportstrategy.h"

class ExportText : public ExportStrategy
{
public:
    ExportText();
	virtual QString			header() const;
	virtual QString			footer() const;
	virtual QString			exportNote(const Note& n, unsigned int level = 0) const;
};

#endif // EXPORTTEXT_H
