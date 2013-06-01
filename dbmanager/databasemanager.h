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
#include "note/classdef.h"
#include "constants.h"

class DatabaseManager
{
public:

	/***************** Getters ***********************/
	const QString getpath() const;

	/******************* Setters *********************/

	/***************** DB REQUESTS ********************/

	/***************** Retrievers *********************/

	std::vector<QString> getAllTags() const; // Retourne tous les Tags existants
	std::vector<QString> getTags (Note& n) const; // Retourne les tags associés ‡ une Note
	std::vector< pair <unsigned int, QString > > getNotes (QString tag) const; // Retourne les Notes associés ‡ un Tag.

	/***************** Deleters ************************/

	bool deleteNote (unsigned int id) const; // On supprime une note
	bool deleteNote () const; // On supprime toutes les notes

	/***************** Inserters **********************/



	template<class noteType>
	unsigned int insertNote() const{
		//Error
		return 0;
	}

	bool insertTag (QString t) const;

	/*
	int insertNote (const Article& a) const; // return the idNote
	int insertNote (const Document& d) const; // return the idNote
	int insertNote (const MultiMedia& m) const; // return the idNote
	bool insertTag (QString t) const;
	*/

	/**************** Updaters ********************/

	bool updateNote (const Article& a)  const;
	bool updateNote (const Document& d)  const;
	bool updateNote (const MultiMedia& m)  const;

	/**************** Fillers ********************/

	bool fillNote (const Article& a)  const;
	bool fillNote (const Document& d)  const;
	bool fillNote (const MultiMedia& m)  const;

	/***************** À Modifier *********************/

	void getNote(unsigned int id) const; // Get 1 note
	void getNote() const; // Get toutes les notes

	/******************* À FAIRE *************************/

	bool deleteTag (QString t) const;
	bool addTagAssoc (Note& n, QString t) const;
	bool removeTagAssoc (Note& n, QString t) const;
	bool addNoteToDoc (Document& d, Note& n) const;
	bool removeNotefromDoc (Document& d, Note& n) const;

	// Singleton
	static DatabaseManager&			getInstance(QString filename = "temp", QString user = "", QString pass = "");
	static void						destroy();

 private:
	QSqlDatabase *database;
	QString dbpath;

	bool initDB();
	bool insertNote (const Note& n) const; // Insère une note
	bool query(QString query) const; // Execute une query en SQL
	int getLastID() const; // Retourne le rowid du de la derniere requete d'insertion effectuée.
	unsigned int insertNote(QString type) const;
	bool insertMultimedia(unsigned int id) const;

	// Singleton
	DatabaseManager(QString filename, QString user, QString pass);	// Interdit l'instanciation directe
	DatabaseManager(const DatabaseManager& nm);	// Interdit la recopie
	DatabaseManager&				operator=(const DatabaseManager& n);	// Interdit la recopie
	static DatabaseManager * s_inst;	// Contient le singleton s'il est instancié
};





#endif // DatabaseManager_H
