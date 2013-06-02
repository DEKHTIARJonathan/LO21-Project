#include "exportstrategy.h"

bool	ExportStrategy::exportFile(const QString &s, const QString &filename, const QString &exportPath, const QString & strategy)
{
	QString fullpath;

	if(strategy.toLower() == "html")
		 fullpath = exportPath+"/"+filename+".html";
	else if (strategy.toLower() == "tex")
		fullpath = exportPath+"/"+filename+".tex";
	else if (strategy.toLower() == "txt")
		fullpath = exportPath+"/"+filename+".txt";
	else
		throw ExportFileException("ExportStrategy::exportFile()","La strategie : "+strategy+" n'existe pas");

	QFile file(fullpath);

	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
		throw ExportFileException("ExportStrategy::exportFile() a généré une erreur avec la strategie : "+strategy, "Erreur à l'ouverture du fichier");

	QTextStream outstream(&file);

	outstream << s.toUtf8();

	return true;
}
