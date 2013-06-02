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

/*bool	ExportText::exportFile(const QString &s, const QString &filename, const QString &exportPath) const
{
	QString fullpath = exportPath+"/"+filename+".txt";
	QFile file(fullpath);

	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
		throw ExportFileException("ExportText::exportFile()", "Erreur à l'ouverture du fichier");

	if(file.write((const char *)s.data()) == -1)
		throw ExportFileException("ExportText::exportFile()", "Erreur à l'écriture dans le fichier");

	return true;
}
*/
