#include "trashdialog.h"
#include "ui_trashdialog.h"

TrashDialog::TrashDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::TrashDialog),
	m_selectedNote(NULL)
{
	ui->setupUi(this);

	// Start search in DataBase
	DatabaseManager& db = DatabaseManager::getInstance();
	std::vector< pair <unsigned int, QString > > result = db.getTrash();

	// Count
	m_trash = result;
	m_count = result.size();

	// Ref
	QListWidget& l = *ui->noteList;

	if(!result.empty()){
		// Display results
		for( std::vector< pair <unsigned int, QString > >::const_iterator it = result.begin(); it!=result.end(); it++ )
			l.addItem( new ListNoteViewItem(it->first,it->second) );
		l.sortItems();
	}

	QObject::connect(ui->noteList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(setSelectedNote(QListWidgetItem*)));
	QObject::connect(ui->emptyTrashButton, SIGNAL(clicked()), this, SLOT(emptyTrash()));
	QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));

}

Note* TrashDialog::getSelectedNote() const{
	return m_selectedNote;
}

bool TrashDialog::isEmpty() const{
	return m_count == 0;
}

void TrashDialog::setSelectedNote(QListWidgetItem* item){
	ListNoteViewItem* i = dynamic_cast<ListNoteViewItem*> ( item );

	if( i!=NULL ){
		m_selectedNote = &NotesManager::getInstance().getNote(i->getId());
		m_count--;
		this->close();
	}
}

void TrashDialog::emptyTrash(){
	NotesManager::getInstance().emptyTrash(m_trash);
	m_count = 0;
	close();
}

TrashDialog::~TrashDialog()
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
