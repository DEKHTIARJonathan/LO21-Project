#include "exporttext.h"
#include "export/generalexportfactory.h"

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

QString	ExportText::exportNote(const Note& n) const
{
	QString titre = n.getTitle();
	return QString(n.metaObject()->className())+"\n\nTitre :\n"+escape(titre)+"\n\n";
}

QString	ExportText::exportNote(const Article& a) const
{
	QString text = a.getText();
	return exportNote((Note&)a)+"Texte :\n"+escape(text);
}

QString	ExportText::exportNote(const Document& d) const
{

	GeneralExportFactory &gef = GeneralExportFactory::getInstance();

	QString result = exportNote((Note&)d);

	for (vector<Note* >::const_iterator it = d.begin(); it != d.end(); it++)
	{

		QString temp = "\t"+gef.exportNoteAsPart("txt", **it).replace ("\n","\n\t")+"\n\n\t-----------------------------------------------\n\n";

		result += temp;
	}
	return result;

	return "";
}

QString	ExportText::exportNote(const Image& i) const
{
	QString description = i.getDescription();
	QString path = i.getPath();
	return exportNote((Note&)i)+"Image :\n"+escape(path)+"\n\nDescription :\n"+escape(description);
}

QString	ExportText::exportNote(const Video& v) const
{
	QString description = v.getDescription();
	QString path = v.getPath();
	return exportNote((Note&)v)+"Video :\n"+escape(path)+"\n\nDescription :\n"+escape(description);
}

QString	ExportText::exportNote(const Audio& a) const
{
	QString description = a.getDescription();
	QString path = a.getPath();
	return exportNote((Note&)a)+"Audio :\n"+escape(path)+"\n\nDescription :\n"+escape(description);
}

QString	ExportText::escape(QString s) const
{
	s.replace("\\", "\\\\");
	return s;
}
