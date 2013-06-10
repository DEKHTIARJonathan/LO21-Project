#include "exportstrategy.h"

bool	ExportStrategy::exportFile(const QString &s, const QString &fullpath)
{

	if( !( fullpath.endsWith(".html") || fullpath.endsWith(".tex") || fullpath.endsWith(".txt") ) )
		throw ExportFileException("ExportStrategy::exportFile()","La strategie : pour le fichier "+fullpath+" n'existe pas");

	QFile file(fullpath);

	if (file.exists())
		throw ExportFileException("ExportStrategy::exportFile() a généré une erreur", "Le Fichier : "+fullpath + " existe deja");

	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
		throw ExportFileException("ExportStrategy::exportFile() a généré une erreur", "Erreur à l'ouverture du fichier");

	QTextStream outstream(&file);

	outstream << s.toUtf8();

	return true;
}
