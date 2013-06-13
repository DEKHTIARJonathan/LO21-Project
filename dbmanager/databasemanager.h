#ifndef DatabaseManager_H
#define DatabaseManager_H

/**
 * \file databasemanager.h
 * \brief Interface entre le logiciel et la base de données. Elle est la seule à réaliser des accès à la BDD
 * \author Dekhtiar Jonathan & Florian Baune
 * \version 1
 */


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
	bool isTrashEmpty() const;
	bool emptyTrash() const;
	bool isTrashed (unsigned int n) const;
	bool putToTrash (unsigned int n) const;
	bool removeFromTrash (unsigned int n) const;

	/***************** Retrievers *********************/

	QStringList getAllTags() const; // Retourne tous les Tags existants
	QStringList getTags (const Note& n) const; // Retourne les tags associés à une Note
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

	bool tagAssocNote (const Note& n, const QStringList& l) const;
	bool tagAssocNote (const Note& n, const QString& t) const;
	bool flushDoc (const Document& d) const;
	bool flushNoteAssoc (const Note& n) const;

	/**************** Fillers ********************/

	bool fillNote (Article& a)  const;
	bool fillNote (Document& d)  const;
	bool fillNote (MultiMedia& m)  const;

	/****************  Singleton *********************/
	/*!
		 *  \brief Méthode static renvoyant une référence sur le singleton DatabaseManager
		 *
		 *  Constructeur de la classe DatabaseManager
		 *
		 *	\param path : chemin du fichier de la base SQLite
		 *  \param user : utilisateur de la base de données
		 *  \param pass : mot de passe de la base de données
		 */
	static DatabaseManager&			getInstance(QString path = QDir::currentPath() +"/temp.lo21", QString user = "", QString pass = "");
	static void						destroy();

 private:

	/******************* Attributs ********************/

	QSqlDatabase *database;
	QString dbpath;

	/***************** DB Requests ********************/
	bool initDB();
	bool query(const QString& query) const; // Execute une query en SQL
	unsigned int getLastID() const; // Retourne le rowid du de la derniere requete d'insertion effectuée.
	bool tagExist(const QString &t) const;

	/********************* Escaper ********************/

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

	/***************** Retrievers **********************/

	bool getNotesInDoc (Document& d) const;

	/***************** AssocBuilders ******************/

	bool addTagAssoc (const Note& n,const QString &t) const;
	bool removeTagAssoc (const Note& n, const QString& t) const;
	bool addNoteToDoc (const Document& d,const Note& n) const;
	bool removeNotefromDoc (const Document& d, const Note& n) const;

	/****************  Singleton ^*********************/
	/*!
		 *  \brief Constructeur
		 *
		 *  Constructeur de la classe DatabaseManager
		 *
		 *  \param path : chemin du fichier de la base SQLite
		 *  \param user : utilisateur de la base de données
		 *  \param pass : mot de passe de la base de données
		 */
	DatabaseManager(const QString &path, const QString &user, const QString &pass);	// Interdit l'instanciation directe

	/*!
		 *  \brief Constructeur de recopie
		 *
		 *  La recopie est interdite

		 */
	DatabaseManager(const DatabaseManager& nm);	// Interdit la recopie

	/*!
		 *  \brief Opérateur =
		 *
		 *  La recopie est interdite
		 */
	DatabaseManager& operator=(const DatabaseManager& n);	// Interdit la recopie


	static DatabaseManager *s_inst;	// Contient le singleton s'il est instancié
	~DatabaseManager();
};

#endif // DatabaseManager_H
