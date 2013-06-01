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

	// Fonction Affichage/Debug
	void printTable() const;

	// Singleton
	static DatabaseManager&			getInstance();
	static void						destroy();

 private:
    QSqlDatabase *database;
	QString dbpath;

    bool initDB();

	// Singleton
	DatabaseManager(QString filename = "temp", QString user = "", QString pass = "");	// Interdit l'instanciation directe
	DatabaseManager(const DatabaseManager& nm);	// Interdit la recopie
	DatabaseManager&				operator=(const DatabaseManager& n);	// Interdit la recopie
	static DatabaseManager * s_inst;	// Contient le singleton s'il est instanci�

};

#endif // DatabaseManager_H
