#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdexcept>
#include <QMainWindow>
#include <QApplication>
#include <QtGui>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QWebFrame>
#include <constants.h>
#include <notemanager/notesmanager.h>
#include <note/multimedia.h>
#include <export/generalexportfactory.h>
#include <view/notesview/generalviewfactory.h>
#include <view/listnoteviewitem.h>
#include <view/trashdialog.h>
#include <view/tagsdialog.h>

#if QT_VERSION >= 0x050000 // Pour la version 5 et + il est nécessaire d'inclure QtWidgets
	#include <QtWidgets>
#endif

namespace Ui {
class MainWindow;
}

//! La MainWindow fait à la fois office de vue principale ainsi que de Controller (design pattern MVC)
/*!
  Au chargement de la fenêtre principale, les fonctions setup***() sont appelées pour finir de configurer la fénêtre principale
  dont la majeur partie de l'implémentation a été réalisé par Qt Designer. Qt Designer qui lorsque les principes de QWidget et Layout sont maîtrisés,
  permet de créer et de configurer rapidement et efficacement des fenêtres, des dialogs...

  L'organisation générale de la classe MainWindow est le suivant:
	- la note courrante, ainsi que la vue de cette dernière contenue dans des poiteurs (NULL si aucunne notes n'est encore ouvertes).
	- un mode édition/mode lecture
	- l'ensemble des actions que l'on peut exécuter sur la MainWindow implémenté dans des Slots qui pourront facilement être activés par les autres composants.
	- un ensemble de méthodes utilitaires privées permetant certainnes actions spécifiques.

  La particularité se trouve au niveau du mode édition. En effet, nous avons mis en place ce mode de manière à éviter la modification involontaire d'une note.
  Cet ajout permet aussi d'annuler plus facilement une modification lorsqu'elle n'a pas encore été sauvegarder.
  Ainsi, lorsque le mode ajout est activé, certaines actions ne sont plus possibles comme par exemples l'export, l'affichage d'une autre note...

  Les tags, étant très indépendant des notes grâce à notre architecture, peuvent être modifié à dans le mode lecture comme dans le mode édition.

  \version	1.0
  \author	Florian Baune & Jonathan Dekhtiar
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

	public slots:
		// Note Management
		//! Slot permettant de créer et d'afficher un nouvel Article.
		/*!
		  Cette fonction affiche un petit message d'erreur si elle est lancé pendant le mode édition.
		  Ce message indique simplement à l'utilisateur qu'il doit terminer le mode édition s'il veut
		  effectuer cette action. Après ce message d'erreur, le déroulement du programme continu sans encombre.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				newArticle();

		//! Slot permettant de créer et d'afficher un nouveau Document.
		/*!
		  Cette fonction affiche un petit message d'erreur si elle est lancé pendant le mode édition.
		  Ce message indique simplement à l'utilisateur qu'il doit terminer le mode édition s'il veut
		  effectuer cette action. Après ce message d'erreur, le déroulement du programme continu sans encombre.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				newDocument();

		//! Slot permettant de créer et d'afficher une nouvelle Image.
		/*!
		  Cette fonction affiche un petit message d'erreur si elle est lancé pendant le mode édition.
		  Ce message indique simplement à l'utilisateur qu'il doit terminer le mode édition s'il veut
		  effectuer cette action. Après ce message d'erreur, le déroulement du programme continu sans encombre.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				newImage();

		//! Slot permettant de créer et d'afficher un nouvel Audio.
		/*!
		  Cette fonction affiche un petit message d'erreur si elle est lancé pendant le mode édition.
		  Ce message indique simplement à l'utilisateur qu'il doit terminer le mode édition s'il veut
		  effectuer cette action. Après ce message d'erreur, le déroulement du programme continu sans encombre.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				newAudio();

		//! Slot permettant de créer et d'afficher une nouvelle Video.
		/*!
		  Cette fonction affiche un petit message d'erreur si elle est lancé pendant le mode édition.
		  Ce message indique simplement à l'utilisateur qu'il doit terminer le mode édition s'il veut
		  effectuer cette action. Après ce message d'erreur, le déroulement du programme continu sans encombre.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				newVideo();

		//! Slot permettant d'ouvrir une note spécifique.
		/*!
		  Précisons que cette fonction est utilisé avec le Signal itemDoubleClicked(QListWidgetItem*) émit
		  par la QListWidget responsable de la recherche de note par tag. Ainsi, l'objet QListWigetItem sera de type
		  réel \sa ListNoteViewItem, si cela n'est pas le cas, cette fonction n'aura aucun effet.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				openNote(QListWidgetItem* i);

		//! Slot permettant d'ouvrir une note spécifique à partir de son id.
		/*!
			Si l'id de la note n'est pas référencé, un message d'erreur apparaîtra tout en permettant de
			continuer l'exécution du programme.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				openNote(unsigned int id);

		//! Slot responsable de l'activation et de la desactivation du mode édition.
		/*!
		  Lorsque le mode édition est désactiver par le biai de ce slot, une sauvegarde des modifications
		  sur la note courrante est effectuée.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				editSaveNote();

		//! Slot responsable de la mise à la corbeille d'une note ainsi que de la désactivation du mode édition.
		/*!
		  En mode lecture, ce slot permet de mettre la note à la corbeille. En mode édition, il permet d'annuler
		  toute les modifications apporter sur la note depuis la dernière sauvegarde.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				deleteCancelNote();

		//! Slot responsable de la boite de dialog de gestion des Tags d'une note.
		/*!
		  Cette fonctionnalité ne fait rien si aucune note n'est actuellement ouverte.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				tagNote();

		//! Slot responsable de la copy des fichiers binaires dans le répertoire courant.
		/*!
		  Cette fonctionnalité ne fait rien en mode édition ou si aucune note n'est actuellement ouverte.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				copyBinaries();
		// Export Management
		//! Slot responsable de l'affichage de l'export html de la note courante.
		/*!
		  Affiche la box d'export correspondante.
		  Cette fonctionnalité ne fait rien si aucune note n'est actuellement ouverte.
		  Et affiche un petit message d'erreur pendant le mode d'édition, empéchant l'export.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				exportNoteAsHtml();

		//! Slot responsable de l'affichage de l'export TeX de la note courante.
		/*!
		  Affiche la box d'export correspondante.
		  Cette fonctionnalité ne fait rien si aucune note n'est actuellement ouverte.
		  Et affiche un petit message d'erreur pendant le mode d'édition, empéchant l'export.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				exportNoteAsTeX();

		//! Slot responsable de l'affichage de l'export Txt de la note courante.
		/*!
		  Affiche la box d'export correspondante.
		  Cette fonctionnalité ne fait rien si aucune note n'est actuellement ouverte.
		  Et affiche un petit message d'erreur pendant le mode d'édition, empéchant l'export.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				exportNoteAsTxt();

		//! Slot responsable de l'affichage de la mise à jours des box Html, TeX ou Txt lorsque sont affichées par l'utilisateur
		/*!
		  Cette fonctionnalité ne fait rien si aucune note n'est actuellement ouverte.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				exportNote(int i);

		//! Slot responsable de l'export de note sous la forme d'un fichier.
		/*!
		  Affiche une boite de dialog demandant la désignation d'un nom de fichier pour l'export.
		  Cette fonction export le fichier au format correspondant à l'affichage de l'export courant.
		  Si aucunne box d'export n'est actuellement afficher, alors cette fonction ne fait rien.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				exportNoteAsFile();
		// Search Management
		//! Slot responsable de la recherche des notes à partir d'un tag
		/*!
		  Si le champs de recherche est vide lorsque la fonction est lancée, on affichera
		  l'ensemble des notes contenues dans la base et qui ne sont pas dans la corbeille.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				searchNotes();
		// Workspace Management
		//! Slot responsable de la création d'un nouveau workspace
		/*!
		  Ouvre une boite de dialog permettant de choisir un nouveau fichier pour un nouveau WorkSpace
		  Et affiche un petit message d'erreur pendant le mode d'édition, empéchant l'export.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				createWorkspace();

		//! Slot responsable de l'ouverture d'un workspace
		/*!
		  Ouvre une boite de dialog permettant de choisir le fichier d'un WorkSpace existant
		  Et affiche un petit message d'erreur pendant le mode d'édition, empéchant l'export.

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				changeWorkspace();
		// Trash Management
		//! Slot responsable de l'ouverture de la boite de dialogue de la corbeille.
		/*!

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				openTrash();

		//! Slot permettant de vider le contenue de la corbeille et donc de détruire physiquement toutes les notes à l'intérieur.
		/*!

		  \version	1.0
		  \author	Florian Baune & Jonathan Dekhtiar
		*/
		void				emptyTrash();
    
	public:
		// Constructor
		explicit MainWindow(QWidget *parent = 0);

		// Destructor
		~MainWindow();
    
	private:
		// Member
		Ui::MainWindow*		ui;
		Note*				m_actualNote;
		NoteView*			m_actualNoteView;
		bool				m_editMode;

		// Info Method
		void				showInfoMessageBox(const QString& msg);
		void				showErrorMessageBox(const QString& msg);

		// Tool Method
		void				newNote(const QString &type);
		void				editNewNote( const QString& NoteType );
		void				displayNote( unsigned int id );
		void				displayNote( Note& n );
		void				clearActualNoteView();
		void				showEditor(bool b);
		void				loadActualNoteContent();
		void				clearListView();
		void				emptyTrash(const std::vector< pair <unsigned int, QString > >& trash);

		// Setup
		void				setupMenu();
		void				setupSearchArea();
		void				setupEditorArea();
		void				setupExportArea();

		// Icons
		void				setTrashIcon(bool empty = true);
};

#endif // MAINWINDOW_H
