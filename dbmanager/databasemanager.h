#ifndef DatabaseManager_H
#define DatabaseManager_H

#include <QWidget>

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QString>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <iostream>
#include <vector>
#include <note/note.h>

class DatabaseManager
{
public:
    /* *************** Constructeur ******************/
	DatabaseManager(QString filename = "temp", QString user = "", QString pass = "");

    /***************** Getters ***********************/
    const QString getpath() const;

    /******************* Setters *********************/

    /***************** DB REQUEST ********************/
	bool query(QString query) const; // Execute une query en SQL
	void getNote(unsigned int id) const; // Get 1 note
	void getNote() const; // Get toutes les notes
	bool deleteNote (unsigned int id) const; // On supprime une note
	bool deleteNote () const; // On supprime toutes les notes
	bool insertNote (QString titre, QString type) const; // Insère une note
	bool addType(QString type) const; // Insère un type de Note dans la DB

    /******************* Temp *************************/

	bool addType() const; // Insère tous les types de Notes dans la DB


	/******************* À FAIRE *************************/

	void getalltags();
	std::vector<QString> getTags (Note& n);
	std::vector<int> getNotes (QString tag);
	bool insertTag (QString t);
	bool deleteTag (QString t);
	bool addTagAssoc (Note& n, QString t);
	bool removeTagAssoc (Note& n, QString t);

 private:
    QSqlDatabase *database;
    QString dbpath;
	DatabaseManager(); // On interdit une construction sans argument
	DatabaseManager(DatabaseManager&); // On interdit une construction par recopie
    bool initDB();

};

#endif // DatabaseManager_H
