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

QString	ExportText::exportNote(const Image& i, unsigned int level) const
{
	return "";
}

QString	ExportText::exportNote(const Video& v, unsigned int level) const
{
	return "";
}

QString	ExportText::exportNote(const Audio& a, unsigned int level) const
{
	return "";
}

QString	ExportText::escape(QString s) const
{
	return s;
}
