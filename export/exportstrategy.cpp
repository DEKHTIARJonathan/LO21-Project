#include "exportstrategy.h"

map<QString,ExportStrategy*> ExportStrategy::s_mapES = map<QString,ExportStrategy*>();

/********************************************************************
 *                          Static Method                           *
 ********************************************************************/

void ExportStrategy::initExportStrategies(){

	// Add every ExportStrategy to s_mapES here ;)
}

ExportStrategy&	ExportStrategy::getExportStrategy(const QString& strategyName){

	map<QString,ExportStrategy*>::iterator res = ExportStrategy::s_mapES.find(strategyName);

	if( res == ExportStrategy::s_mapES.end() )
		throw ExportStrategyNotFoundException(strategyName.toStdString());

	return *(res->second);
}
