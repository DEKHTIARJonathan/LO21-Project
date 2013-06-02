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

/*bool	ExportTex::exportFile(const QString &s, const QString &filename, const QString &exportPath) const
{
	QString fullpath = exportPath+"/"+filename+".tex";
	QFile file(fullpath);

	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
		throw ExportFileException("ExportTex::exportFile()", "Erreur à l'ouverture du fichier");

	if(file.write((const char *)s.data()) == -1)
		throw ExportFileException("ExportTex::exportFile()", "Erreur à l'écriture dans le fichier");

	return true;
}*/
