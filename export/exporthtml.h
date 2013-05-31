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
    virtual QString			header() const;
    virtual QString			footer() const;
    virtual QString			exportNote(const Note& n, unsigned int level = 0) const;

};

#endif // EXPORTHTML_H
