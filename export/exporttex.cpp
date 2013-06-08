#include "exporttex.h"
#include "export/generalexportfactory.h"
ExportTex::ExportTex()
{
}


QString	ExportTex::header() const
{
	return "\\documentclass[11pt,a4paper]{article}\n"
			"\\usepackage[UKenglish]{babel}\n"
			"\\usepackage{multimedia}\n";
}

QString	ExportTex::footer() const
{
	return "\\end{document}\n";
}

QString	ExportTex::exportNote(const Note& n) const
{
	QString titre = n.getTitle();
	return "\\title{"+escape(titre)+"}\n"
			"\\begin{document}\n"
			"\\maketitle\n";
}

QString	ExportTex::exportNote(const Article& a) const
{
	QString text = a.getText();
	return exportNote((Note&)a)+"\\section*{Text: }\n"
			""+escape(text)+"\n";
}

QString	ExportTex::exportNote(const Document& d) const
{
	GeneralExportFactory &gef = GeneralExportFactory::getInstance();

	QString result = exportNote((Note&)d);

	for (vector<Note* >::const_iterator it = d.begin(); it != d.end(); it++)
	{
		result += "\\frame\n"
				  "{\n"
				  ""+gef.exportNoteAsPart("tex", **it)+"\n"
				  "}\n";
	}
	return result;
}

QString	ExportTex::exportNote(const Image& i) const
{
	QString desc = i.getDescription();
	QString path = i.getPath();
	return exportNote((Note&)i)+"\\section*{Video: }\n"
			"\\frame\n"
			"{\n"
				"\\includegraphics{"+escape(path)+"}\n"
			"}\n"
	"Description : \n"+escape(desc)+"\n";
}

QString	ExportTex::exportNote(const Video& v) const
{
	QString desc = v.getDescription();
	QString path = v.getPath();
	return exportNote((Note&)v)+"\\section*{Video: }\n"
			"\\frame\n"
			"{\n"
				"\\movie{"+escape(path)+"}\n"
			"}\n"
			"Description : \n"+escape(desc)+"\n";
}

QString	ExportTex::exportNote(const Audio& a) const
{
	QString desc = a.getDescription();
	QString path = a.getPath();
	return exportNote((Note&)a)+"\\section*{Video: }\n"
			"\\frame\n"
			"{\n"
				"\\audio{"+escape(desc)+"}\n"
			"}\n"
			"Description : \n"+escape(path)+"\n";
}

QString	ExportTex::escape(QString s) const
{
	s.replace("\\", "\\textbackslash");
	s.replace("&", "\\&");
	s.replace("$", "\\$");
	s.replace("%", "\\%");
	s.replace("#", "\\#");
	s.replace("_", "\\_");
	s.replace("{", "\\{");
	s.replace("}", "\\}");
	s.replace("^", "\\textasciicircum");
	s.replace("~", "\\textasciitilde");
	s.replace("<", "\\textless{}");
	s.replace(">", "\\textgreater{}");

	return s;
}
