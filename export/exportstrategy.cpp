#include "exportstrategy.h"

bool	ExportStrategy::exportFile(const QString &s, const QString &filename, const QString & strategy, const QDir exportPath)
{
	QString fullpath;

	if (!exportPath.exists())
		throw ExportFileException("ExportStrategy::exportFile() a généré une erreur avec la strategie : "+strategy, "Le Chemin : "+ exportPath.path() + " n'existe pas");

	if(strategy.toLower() == "html")
		 fullpath = exportPath.path()+"/"+filename+".html";
	else if (strategy.toLower() == "tex")
		fullpath = exportPath.path()+"/"+filename+".tex";
	else if (strategy.toLower() == "txt")
		fullpath = exportPath.path()+"/"+filename+".txt";
	else
		throw ExportFileException("ExportStrategy::exportFile()","La strategie : "+strategy+" n'existe pas");

	QFile file(fullpath);

	if (file.exists())
		throw ExportFileException("ExportStrategy::exportFile() a généré une erreur avec la strategie : "+strategy, "Le Fichier : "+fullpath + " existe deja");

	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
		throw ExportFileException("ExportStrategy::exportFile() a généré une erreur avec la strategie : "+strategy, "Erreur à l'ouverture du fichier");

	QTextStream outstream(&file);

	outstream << s.toUtf8();

	return true;
}
