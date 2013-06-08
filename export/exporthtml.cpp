#include "exporthtml.h"

ExportHTML::ExportHTML() : ExportStrategy()
{}

QString	ExportHTML::header() const
{
    return "<html>"
           "<head>"
			"<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\">"
            "</head>"
            "<body>";
}

QString	ExportHTML::footer() const
{
    return "</body>"
            "</html>";
}

QString	ExportHTML::exportNote(const Note& n) const
{
	QString titre = n.getTitle();
	return "<div><h1>"+escape(titre)+"</h1></div>";
}

QString	ExportHTML::exportNote(const Article& a) const
{
	QString text = a.getText();
	return exportNote((Note&)a)+"<div><h2>Texte :</h2><br><p>"+escape(text)+"</p></div>";
}

QString	ExportHTML::exportNote(const Document& d) const
{
	d.getTitle();
	return "";
}

QString	ExportHTML::exportNote(const Image& i) const
{
	QString description = i.getDescription();

	QString path =  i.getPath();

	if (!path.startsWith("http"))
		 path = "file://"+path;

	return exportNote((Note&)i)+"<div><h2>Image :</h2><br><img src='"+escape(path)+"'><br><h3>Description</h3><p>"+escape(description)+"</p></div>";
}

QString	ExportHTML::exportNote(const Video& v) const
{
	QString description = v.getDescription();
	QString path = v.getPath();
	return exportNote((Note&)v)+"<div><h2>Video :</h2><br>"
			"<video id=\"sampleMovie\" width=\"640\" height=\"360\" preload controls><source src=\""+escape(path)+"\"/></video>"
			"<br><h3>Description</h3><p>En cas de problème à la lecture . Le navigateur ne doit pas être compatible avec le lecteur</p>"
			"<p>"+escape(description)+"</p></div>";

}

QString	ExportHTML::exportNote(const Audio& a) const
{
	QString description = a.getDescription();
	QString path = a.getPath();
	return exportNote((Note&)a)+"<div><h2>Audio :</h2><br>"
			"<audio preload=\"auto\" autobuffer controls id=\"audio\"><source src=\""+escape(path)+"\" type=\"audio/mpeg\"></audio>"
			"<br><h3>Description</h3><p>En cas de problème à la lecture . Le navigateur ne doit pas être compatible avec le lecteur</p>"
			"<p>"+escape(description)+"</p></div>";
}


QString	ExportHTML::escape(QString s) const
{
	s.replace("\\", "\\\\");
	return s;
}


