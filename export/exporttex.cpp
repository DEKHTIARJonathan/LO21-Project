#include "exporttex.h"

ExportTex::ExportTex()
{
}


/*

			  % section header, defined by article class

\TeX\ is a typesetting language. Instead of visually formatting your text, you type
your text combined with commands in a plain text file.

You can use macro packages like \LaTeX.
TeX is a superb typesetter and is therefore very good at formulas: \[\Omega_0 = \left (
\frac{\alpha}{\beta} \right ) ^ 4\]

\end{document}





  */


QString	ExportTex::header() const
{
	return "\\documentclass[11pt,a4paper]{article}\n"
			"\\usepackage[UKenglish]{babel}\n";
}

QString	ExportTex::footer() const
{
	return "\\end{document}\n";
}

QString	ExportTex::exportNote(const Note& n, unsigned int level) const
{
	QString titre = n.getTitle();
	return "\\title{"+escape(titre)+"}\n"
			"\\begin{document}\n"
			"\\maketitle\n";
}

QString	ExportTex::exportNote(const Article& a, unsigned int level) const
{
	QString text = a.getText();
	return exportNote((Note&)a)+"\\section*{Text: }\n"
			""+escape(text)+"\n";
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
	s.replace("\\", "\\textbackslash");
	s.replace("&", "\&");
	s.replace("$", "\$");
	s.replace("%", "\%");
	s.replace("#", "\#");
	s.replace("_", "\_");
	s.replace("{", "\{");
	s.replace("}", "\}");
	s.replace("^", "\\textasciicircum");
	s.replace("~", "\\textasciitilde");
	s.replace("<", "\\textless{}");
	s.replace(">", "\\textgreater{}");

	return s;
}
