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
	QString titre = n.getTitle();
	return "Article\n\nTitre :\n"+escape(titre)+"\n\n";
}

QString	ExportText::exportNote(const Article& a, unsigned int level) const
{
	QString text = a.getText();
	return exportNote((Note&)a)+"Texte :\n"+escape(text);
}

QString	ExportText::exportNote(const Document& d, unsigned int level) const
{
	return "";
}

QString	ExportText::exportNote(const Image& i, unsigned int level) const
{
	QString description = i.getDescription();
	QString path = i.getPath();
	return exportNote((Note&)i)+"Image :\n"+escape(path)+"'\n\nDescription :\n"+escape(description);
}

QString	ExportText::exportNote(const Video& v, unsigned int level) const
{
	QString description = v.getDescription();
	QString path = v.getPath();
	return exportNote((Note&)v)+"Video :\n"+escape(path)+"'\n\nDescription :\n"+escape(description);
}

QString	ExportText::exportNote(const Audio& a, unsigned int level) const
{
	QString description = a.getDescription();
	QString path = a.getPath();
	return exportNote((Note&)a)+"Audio :\n"+escape(path)+"'\n\nDescription :\n"+escape(description);
}

QString	ExportText::escape(QString s) const
{
	s.replace("\\", "\\\\");
	return s;
}
