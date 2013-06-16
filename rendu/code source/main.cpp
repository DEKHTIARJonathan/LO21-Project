#include <QApplication>
#include <QtGui>
#include <export/exportstrategy.h>
#include <iostream>
#include <stdexcept>

#include <note/classdef.h>
#include <dbmanager/databasemanager.h>
#include <notefactory/generalnotefactory.h>
#include <QApplication>
#include <view/mainwindow.h>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MainWindow w;
	w.show();

	return app.exec();
}