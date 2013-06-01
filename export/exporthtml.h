#ifndef EXPORTHTML_H
#define EXPORTHTML_H

#include <QString>
#include <iostream>
#include "exportstrategy.h"
#include "note/classdef.h"

class ExportHTML : public ExportStrategy
{
public:
	ExportHTML();
	QString			header() const;
	QString			footer() const;
	QString			exportNote(const Note& n, unsigned int level = 0) const;
	QString			exportNote(const Article& n, unsigned int level = 0) const;

};

#endif // EXPORTHTML_H
