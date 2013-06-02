#include "exporttex.h"

ExportTex::ExportTex()
{
}

QString	ExportTex::header() const
{
	return "\\documentclass{article}" "\n" "\\begin{document}";
}

QString	ExportTex::footer() const
{
	return "\\end{document}";
}

QString	ExportTex::exportNote(const Note& n, unsigned int level) const
{
	return "";
}

QString	ExportTex::exportNote(const Article& a, unsigned int level) const
{
	return "";
}

QString	ExportTex::exportNote(const Document& d, unsigned int level) const
{
	return "";
}

QString	ExportTex::exportNote(const Image& i, unsigned int level) const
{
	return "";
}

QString	ExportTex::exportNote(const Video& v, unsigned int level) const
{
	return "";
}

QString	ExportTex::exportNote(const Audio& a, unsigned int level) const
{
	return "";
}


QString	ExportTex::escape(QString s) const
{
	return s;
}
