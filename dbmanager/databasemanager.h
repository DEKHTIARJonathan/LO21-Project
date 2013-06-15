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
	/*!
		 *  \brief Renvoie le path du fichier SQLite de la base de donnée
		 */
	const QString getpath() const;

	/******************* Setters **********************/

	/***************** DB REQUESTS ********************/

	/***************** TrashManaging ******************/
	/*!
		 *  \brief Renvoie un booléen précisant si la corbeille est vide
		 */
	bool isTrashEmpty() const;

	/*!
		 *  \brief Renvoie un booléen précisant si le vidage de corbeille s'est bien passé.
		 */
	bool emptyTrash() const;

	/*!
		 *  \brief Renvoie un booléen précisant si la note d'id n est dans la poubelle
		 *  \param n : id de la note à checker
		 */
	bool isTrashed (unsigned int n) const;

	/*!
		 *  \brief Renvoie un booléen précisant si la note a bien été mise à la poubelle
		 *  \param n : id de la note à mettre à la poubelle
		 */
	bool putToTrash (unsigned int n) const;

	/*!
		 *  \brief Renvoie un booléen précisant si la note d'id n a bien été retiré de la poubelle
		 *  \param n : id de la note à retirer de la poubelle
		 */
	bool removeFromTrash (unsigned int n) const;

	/***************** Retrievers *********************/
	/*!
		 *  \brief Renvoie une QStringList de tous les tags existant
		 */
	QStringList getAllTags() const; // Retourne tous les Tags existants

	/*!
		 *  \brief Renvoie une QStringList de tous les tags associés à une Note n
		 *  \param n : Note
		 */
	QStringList getTags (const Note& n) const; // Retourne les tags associés à une Note

	/*!
		 *  \brief renvoie un vecteur de paires contenant l'id d'une note et le titre d'une note.
		 *Chacune de ces Notes doivent être taguées par le tag passé en argument
		 *Cette fonction renvoie uniquement les notes qui ne sont pas à la poubelle
		 *
		 *  \param tag : Le tag dont on veut effectuer la recherche
		 */
	std::vector< pair <unsigned int, QString > > getNotes (const QString &tag) const; // Retourne les Notes associés à un Tag.

	/*!
		 *  \brief renvoie un vecteur de paires contenant l'id d'une note et le titre d'une note.
		 * Cette fonction renvoie toutes les notes qui ne sont pas à la poubelle
		 */
	std::vector< pair <unsigned int, QString > > getNotes () const; // Retourne Toutes les Notes

	/*!
		 *  \brief renvoie un vecteur de paires contenant l'id d'une note et le titre d'une note.
		 * Cette fonction renvoie toutes les notes qui sont dans la poubelle
		 */
	std::vector< pair <unsigned int, QString > > getTrash() const;

	/*!
		 *  \brief renvoie une QString contenant le type de la note dont l'id est passé en argument
		 *
		 *  \param tag : id de la note
		 */
	QString getNoteType(const unsigned int id); // Renvoie le type d'une note

	/***************** Deleters ************************/
	/*!
		 *  \brief renvoie un booléen indiquant la réussite de la suppression du tag t.
		 *
		 *  \param t : Le tag que l'on veut supprimer
		 */
	bool deleteTag (const QString &t) const; // On supprime un Tag

	/*!
		 *  \brief on réinitialise la DB, on la vide complètement : Note + Tag
		 */
	bool flushDB () const; // On vide complètement la base de données

	/***************** Inserters **********************/

	/*!
		 *  \brief insère une note du type passé en argument et renvoie l'id de la note insérée.
		 *
		 *  \param typeNote : Le type de la note que l'on veut insérer dans la base
		 */
	unsigned int insertNote(const QString& typeNote) const;

	/**************** Updaters ********************/

	/*!
		 *  \brief on update (=sauvegarde) dans la base l'état actuel d'une article
		 *
		 *  \param a : L'article que l'on veut sauvegarder dans la base
		 */
	bool updateNote (const Article& a)  const;

	/*!
		 *  \brief on update (=sauvegarde) dans la base l'état actuel d'un Document
		 *
		 *  \param d : Le Document que l'on veut sauvegarder dans la base
		 */
	bool updateNote (const Document& d)  const;

	/*!
		 *  \brief on update (=sauvegarde) dans la base l'état actuel d'une video/image/audio
		 *
		 *  \param m : La video/image/audio que l'on veut sauvegarder dans la base
		 */
	bool updateNote (const MultiMedia& m)  const;

	/********** AssocBuilders // AssocRemovers **********/

	/*!
		 *  \brief On associe une Note à un ensemble de tag, renvoie un bool sur la réussite de l'opération
		 *
		 *  \param l : QStringList de tag que l'on veut associer à la note
		 */
	bool tagAssocNote (const Note& n, const QStringList& l) const;

	/*!
		 *  \brief On associe une Note à un tag, renvoie un bool sur la réussite de l'opération
		 *
		 *  \param t : Un tag que l'on veut associer à la note
		 */
	bool tagAssocNote (const Note& n, const QString& t) const;

	/*!
		 *  \brief Vide entièrement un document, renvoie un bool sur la réussite de l'opération
		 *
		 *  \param d : le document que l'on veut vider
		 */
	bool flushDoc (const Document& d) const;

	/*!
		 *  \brief Enlève tous les tags d'une note, renvoie un bool sur la réussite de l'opération
		 *
		 *  \param n : la note que l'on veut détaguer
		 */
	bool flushNoteAssoc (const Note& n) const;

	/**************** Fillers ********************/
	/*!
		 *  \brief Remplit les attributs d'un article en important les données de la DB
		 * Renvoie un bool sur la réussite de l'opération
		 *
		 *  \param a : l'article que l'on veut remplir
		 */
	bool fillNote (Article& a)  const;

	/*!
		 *  \brief Remplit les attributs d'un document en important les données de la DB
		 * Renvoie un bool sur la réussite de l'opération
		 *
		 *  \param d : le document que l'on veut remplir
		 */
	bool fillNote (Document& d)  const;

	/*!
		 *  \brief Remplit les attributs d'une video/image/audio en important les données de la DB
		 * Renvoie un bool sur la réussite de l'opération
		 *
		 *  \param m : la video/image/audio que l'on veut remplir
		 */
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

	/*!
		 *  \brief Méthode static détruisant le singleton
		 */
	static void						destroy();

 private:

	/******************* Attributs ********************/

	QSqlDatabase *database;
	QString dbpath;

	/***************** DB Requests ********************/
	/*!
		 *  \brief Initialise les tables de la DB et la structure complète de notre modèle relationnel.
		 */
	bool initDB();

	/*!
		 *  \brief Éxécute une query passée en argument, renvoie un bool sur la réussite de l'opération
		 *
		 *  \param query : la query que l'on veut éxécuter
		 */
	bool query(const QString& query) const; // Execute une query en SQL

	/*!
		 *  \brief Renvoie le dernier ID inséré dans la table Note.
		 */
	unsigned int getLastID() const; // Retourne le rowid du de la derniere requete d'insertion effectuée.

	/*!
		 *  \brief Renvoie un booléen raportant l'existance d'un tag
		 *
		 *  \param t : le tag dont on cherche à connaitre l'existance
		 */
	bool tagExist(const QString &t) const;

	/********************* Escaper ********************/
	/*!
		 *  \brief Escape une query de manière à limiter les injections SQL
		 *
		 *  \param s : la query que l'on cherche à escape
		 */
	QString escape(QString s) const;

	/*!
		 *  \brief Renvoie une QString avec la première lettre en majuscule et les autres en minuscule : "Exemple"
		 *
		 *  \param str : la string que l'on veut capitalize
		 */
	QString capitalize(QString str) const;

	/***************** Deleters ***********************/
	/*!
		 *  \brief Supprime la Note dont l'id est passé en argument , renvoie un bool sur la réussite de l'opération
		 *
		 *  \param id : id de la note que l'on veut supprimer
		 */
	bool deleteNote (unsigned int id) const;

	/*!
		 *  \brief Supprime toutes les Notes de la base
		 */
	bool deleteNote () const; // On supprime toutes les notes

	/*!
		 *  \brief Supprime tous les tags de la base
		 */
	bool deleteTag () const; // On supprime tous les Tag

	/***************** Inserters **********************/
	/*!
		 *  \brief Insère la partie commune à toutes les notes dans la base et renvoie l'id de cette note
		 *
		 * \param type : Type de la Note qu'on insère
		 */
	unsigned int insertNoteCommon(const QString& type) const;

	/*!
		 *  \brief Insère la partie spécifique d'une Note Audio/Video/Image
		 *
		 *  \param id : id de la video/image/audio que l'on insère
		 */
	bool insertMultimedia(const unsigned int id) const;

	/***************** Retrievers **********************/

	/*!
		 *  \brief Remplis le document avec les notes qui lui sont associées.
		 *
		 *  \param d : Document que l'on veut remplir
		 */
	bool getNotesInDoc (Document& d) const;

	/***************** AssocBuilders ******************/
	/*!
		 *  \brief Associe un Tag et Une Note
		 *
		 *  \param n : la note que l'on veut associer
		 *
		 *	\param t : le tag que l'on veut associer
		 */
	bool addTagAssoc (const Note& n,const QString &t) const;

	/*!
		 *  \brief Désssocie un Tag et Une Note
		 *
		 *  \param n : la note que l'on veut désassocier
		 *
		 *	\param t : le tag que l'on veut désassocier
		 */

	bool removeTagAssoc (const Note& n, const QString& t) const;

	/*!
		 *  \brief Ajoute une Note dans un Document
		 *
		 *  \param n : la note que l'on veut ajouter
		 *
		 *	\param d : le document concerné
		 */
	bool addNoteToDoc (const Document& d,const Note& n) const;

	/*!
		 *  \brief Enleve une note d'un document
		 *
		 *  \param n : la note que l'on veut enlever
		 *
		 *	\param d : le document concerné
		 */
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

	/*!
		 *  \brief La destruction est interdite
		 */
	~DatabaseManager();
};

#endif // DatabaseManager_H
