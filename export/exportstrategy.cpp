#include "exportstrategy.h"

#include "export/exporthtml.h"

QHash<QString,ExportStrategy*> ExportStrategy::s_mapES = QHash<QString,ExportStrategy*>();

/********************************************************************
 *                          Static Method                           *
 ********************************************************************/

void ExportStrategy::initExportStrategies()
{

	ExportStrategy::s_mapES.insert("html",new ExportHTML());

}

ExportStrategy&	ExportStrategy::getExportStrategy(const QString& strategyName)
{

	QHash<QString,ExportStrategy*>::iterator res = ExportStrategy::s_mapES.find(strategyName);

	if( res == ExportStrategy::s_mapES.end() )
		throw ExportStrategyNotFoundException(strategyName);

	return **res;
}
