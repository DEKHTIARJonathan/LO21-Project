#include <QApplication>
#include <QtGui>
#include <export/exportstrategy.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	ExportStrategy::initExportStrategies();
	ExportStrategy::getExportStrategy("Test");

    return app.exec();
}
