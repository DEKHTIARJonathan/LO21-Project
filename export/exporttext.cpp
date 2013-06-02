#include "exporttext.h"

ExportText::ExportText()
{

}

QString	ExportText::header() const
{
	return "";
}

QString	ExportText::footer() const
{
	return "";
}

QString	ExportText::exportNote(const Note& n, unsigned int level) const
{
	return "";
}

QString	ExportText::exportNote(const Article& a, unsigned int level) const
{
	return "";
}

QString	ExportText::exportNote(const Document& d, unsigned int level) const
{
	return "";
}

QString	ExportText::exportNote(const MultiMedia& m, unsigned int level) const
{
	return "";
}

QString	ExportText::escape(QString s) const
{
	return s;
}
