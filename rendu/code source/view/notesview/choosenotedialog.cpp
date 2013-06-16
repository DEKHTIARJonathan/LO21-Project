#include "choosenotedialog.h"
#include "ui_choosenotedialog.h"

ChooseNoteDialog::ChooseNoteDialog(const QList<unsigned int>& forbidIds, QWidget *parent) :
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
			if( !forbidIds.contains(it->first) )
				l.addItem( new ListNoteViewItem(it->first,it->second) );
		l.sortItems();
	}

	QObject::connect(ui->noteList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(setSelectedNote(QListWidgetItem*)));
	QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));

}

Note* ChooseNoteDialog::getSelectedNote() const{
	return m_selectedNote;
}

void ChooseNoteDialog::setSelectedNote(QListWidgetItem* item){
	ListNoteViewItem* i = dynamic_cast<ListNoteViewItem*> ( item );

	if( i!=NULL ){
		m_selectedNote = &NotesManager::getInstance().getNote(i->getId());
		this->close();
	}
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
