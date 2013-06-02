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

QString	ExportHTML::exportNote(const Note& n, unsigned int level) const
{
	QString titre = n.getTitle();
	return "<div><h1>"+escape(titre)+"</h1></div>";
}

QString	ExportHTML::exportNote(const Article& a, unsigned int level) const
{
	QString text = a.getText();
	return exportNote((Note&)a)+"<div><h2>Texte :</h2><br><p>"+escape(text)+"</p></div>";
}

QString	ExportHTML::exportNote(const Document& d, unsigned int level) const
{
	return "";
}

QString	ExportHTML::exportNote(const Image& i, unsigned int level) const
{
	QString description = i.getDescription();
	QString path = i.getPath();
	return exportNote((Note&)i)+"<div><h2>Image :</h2><br><img src='"+escape(path)+"'><br><h3>Description</h3><p>"+escape(description)+"</p></div>";
}

QString	ExportHTML::exportNote(const Video& v, unsigned int level) const
{
	QString description = v.getDescription();
	QString path = v.getPath();
	return exportNote((Note&)v)+"<div><h2>Image :</h2><br><img src='"+escape(path)+"'><br><h3>Description</h3><p>"+escape(description)+"</p></div>";
}

QString	ExportHTML::exportNote(const Audio& a, unsigned int level) const
{
	return "";
}


QString	ExportHTML::escape(QString s) const
{
	return s;
}
