#ifndef DatabaseManager_H
#define DatabaseManager_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <iostream>
#include <vector>
#include "note/classdef.h"
#include "constants.h"
#include <dbmanager/dbexception.h>

class DatabaseManager
{
public:

	/***************** Getters ************************/
	const QString getpath() const;

	/******************* Setters **********************/

	/***************** DB REQUESTS ********************/

	/***************** TrashManaging ******************/

	bool emptyTrash() const;
	bool isTrashed (unsigned int n) const;
	bool putToTrash (unsigned int n) const;
	bool removeFromTrash (unsigned int n) const;


	/***************** Retrievers *********************/

	std::vector<QString> getAllTags() const; // Retourne tous les Tags existants
	std::vector<QString> getTags (const Note& n) const; // Retourne les tags associés à une Note
	std::vector< pair <unsigned int, QString > > getNotes (const QString &tag) const; // Retourne les Notes associés à un Tag.
	std::vector< pair <unsigned int, QString > > getNotes () const; // Retourne Toutes les Notes
	std::vector< pair <unsigned int, QString > > getTrash() const;
	QString getNoteType(const unsigned int id); // Renvoie le type d'une note

	/***************** Deleters ************************/

	bool deleteTag (const QString &t) const; // On supprime un Tag
	bool flushDB () const; // On vide complètement la base de données

	/***************** Inserters **********************/

	unsigned int insertNote(const QString& typeNote) const;

	/**************** Updaters ********************/

	bool updateNote (const Article& a)  const;
	bool updateNote (const Document& d)  const;
	bool updateNote (const MultiMedia& m)  const;

	/********** AssocBuilders // AssocRemovers **********/

	bool TagAssocNote (const Note& n, const QString& t) const;
	bool removeTagAssoc (const Note& n, const QString& t) const;
	bool addNoteToDoc (const Document& d,const Note& n) const;
	bool removeNotefromDoc (const Document& d, const Note& n) const;
	bool flushNoteAssoc (const Note& n) const;

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
	bool query(const QString& query) const; // Execute une query en SQL
	int getLastID() const; // Retourne le rowid du de la derniere requete d'insertion effectuée.
	bool tagExist(const QString &t) const;

	/********************* ESCAPER ********************/

	QString escape(QString s) const;
	QString capitalize(QString str) const;

	/***************** Deleters ***********************/

	bool deleteNote (unsigned int id) const;
	bool deleteNote () const; // On supprime toutes les notes
	bool deleteTag () const; // On supprime tous les Tag

	/***************** Inserters **********************/

	unsigned int insertNoteCommon(const QString& type) const;
	bool insertMultimedia(const unsigned int id) const;
	bool insertTag (const QString &t) const;

	/***************** AssocBuilders ******************/

	bool addTagAssoc (const Note& n,const QString &t) const;

	/****************  Singleton ^*********************/

	DatabaseManager(const QString &filename, const QString &user, const QString &pass);	// Interdit l'instanciation directe
	DatabaseManager(const DatabaseManager& nm);	// Interdit la recopie
	DatabaseManager& operator=(const DatabaseManager& n);	// Interdit la recopie
	static DatabaseManager * s_inst;	// Contient le singleton s'il est instancié
};

#endif // DatabaseManager_H
