#include "exporthtml.h"

ExportHTML::ExportHTML() : ExportStrategy()
{}

QString	ExportHTML::header() const
{
    return "<html>"
           "<head>"
            "</head>"
            "<body>";
}

QString	ExportHTML::footer() const
{
    return "</body>"
            "</html>";
}

QString	ExportHTML::exportNote(const Note &n, unsigned int level) const
{
	return "Note Connard !!!";
}

QString	ExportHTML::exportNote(const Article &n, unsigned int level) const
{
	return "Article Connard !!!";
}

QString	ExportHTML::escape(QString s) const
{
	return s;
}
