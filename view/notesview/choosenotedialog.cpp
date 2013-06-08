#include "choosenotedialog.h"
#include "ui_choosenotedialog.h"

ChooseNoteDialog::ChooseNoteDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ChooseNoteDialog),
	m_selectedNote(NULL)
{
	ui->setupUi(this);

	// Start search in DataBase
	DatabaseManager& db = DatabaseManager::getInstance();
	std::vector< pair <unsigned int, QString > > result = db.getNotes();

	QListWidget& l = *ui->noteList;

	if(!result.empty()){
		// Display results
		for( std::vector< pair <unsigned int, QString > >::const_iterator it = result.begin(); it!=result.end(); it++ )
			l.addItem( new ListNoteViewItem(it->first,it->second) );
		l.sortItems();
	}


}

Note& ChooseNoteDialog::getSelectedNote() const{
	return *m_selectedNote;
}

void ChooseNoteDialog::setSelectedNote(Note& n){
	m_selectedNote = &n;

}

ChooseNoteDialog::~ChooseNoteDialog()
{
	// Clear List View
	QListWidget& l = *ui->noteList;
	QListWidgetItem* item = l.takeItem(0);
	while( item != NULL ){
		delete item;
		item = l.takeItem(0);
	}

	delete ui;
}
