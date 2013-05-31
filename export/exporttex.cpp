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
