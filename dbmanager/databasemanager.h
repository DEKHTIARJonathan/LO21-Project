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
	std::vector< pair <unsigned int, QString > > getNotes () const; // Retourne Toutes les Notes

	QString getNoteType(unsigned int id); // Renvoie le type d'une note

	/***************** Deleters ************************/

	bool deleteNote (unsigned int id) const; // On supprime une note
	bool deleteNote () const; // On supprime toutes les notes
	bool deleteTag (QString t) const; // On supprime un Tag
	bool deleteTag () const; // On supprime tous les Tag

	/***************** Inserters **********************/

	unsigned int insertNote(const QString& typeNote) const;
/*
	template<class noteType>
	unsigned int insertNote() const{
		//Error
		return 0;
	}
*/
	bool insertTag (QString t) const;


	/**************** Updaters ********************/

	bool updateNote (const Article& a)  const;
	bool updateNote (const Document& d)  const;
	bool updateNote (const MultiMedia& m)  const;

	/********** AssocBuilders // AssocRemovers **********/

	bool addTagAssoc (Note& n, QString t) const;
	bool removeTagAssoc (Note& n, QString t) const;
	bool addNoteToDoc (Document& d, Note& n) const;
	bool removeNotefromDoc (Document& d, Note& n) const;

	/**************** Fillers ********************/

	bool fillNote (Article& a)  const;
	bool fillNote (Document& d)  const;
	bool fillNote (MultiMedia& m)  const;

	/****************  Singleton ^*********************/
	static DatabaseManager&			getInstance(QString filename = "temp", QString user = "", QString pass = "");
	static void						destroy();

 private:

	/******************* Attributs ********************/

	QSqlDatabase *database;
	QString dbpath;

	/***************** DB REQUESTS ********************/
	bool initDB();
	bool query(QString query) const; // Execute une query en SQL
	int getLastID() const; // Retourne le rowid du de la derniere requete d'insertion effectuée.

	/***************** Inserters **********************/

	unsigned int insertNotePrivate(const QString& type) const;
	bool insertMultimedia(unsigned int id) const;

	/****************  Singleton ^*********************/

	DatabaseManager(QString filename, QString user, QString pass);	// Interdit l'instanciation directe
	DatabaseManager(const DatabaseManager& nm);	// Interdit la recopie
	DatabaseManager&				operator=(const DatabaseManager& n);	// Interdit la recopie
	static DatabaseManager * s_inst;	// Contient le singleton s'il est instancié
};

#endif // DatabaseManager_H
