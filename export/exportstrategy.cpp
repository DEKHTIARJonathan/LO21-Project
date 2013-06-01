#include "exportstrategy.h"

#include "export/exporthtml.h"

map<QString,ExportStrategy*> ExportStrategy::s_mapES = map<QString,ExportStrategy*>();

/********************************************************************
 *                          Static Method                           *
 ********************************************************************/

void ExportStrategy::initExportStrategies(){

	ExportStrategy::s_mapES.insert(s_mapES.begin(), std::pair<QString,ExportStrategy*>("html",new ExportHTML()));

}

ExportStrategy&	ExportStrategy::getExportStrategy(const QString& strategyName){

	map<QString,ExportStrategy*>::iterator res = ExportStrategy::s_mapES.find(strategyName);

	if( res == ExportStrategy::s_mapES.end() )
		throw ExportStrategyNotFoundException(strategyName.toStdString());

	return *(res->second);
}
