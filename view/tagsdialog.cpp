#include "tagsdialog.h"
#include "ui_tagsdialog.h"

/********************************************************************
 *                            Constructor                           *
 ********************************************************************/

TagsDialog::TagsDialog(Note& n, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::TagsDialog),
	m_note(n),
	m_isCancelled(true)
{
	ui->setupUi(this);

	// Start search in DataBase
	DatabaseManager& db = DatabaseManager::getInstance();
	QStringList tags = db.getAllTags();
	QStringList selectedTags = db.getTags(m_note);
	m_tagsList = tags;

	// Setup
	QListWidget& l = *ui->tagsList;
	l.setSelectionMode(QAbstractItemView::NoSelection);

	if(!tags.isEmpty()){
		// Display All Tags
		for( QStringList::ConstIterator it = tags.begin(); it!=tags.end(); it++ ){
			// Create tag item
			QListWidgetItem* tagItem = new QListWidgetItem(*it, &l);
			tagItem->setFlags(tagItem->flags() | Qt::ItemIsUserCheckable);
			if( selectedTags.contains(*it, Qt::CaseInsensitive) )
				tagItem->setCheckState(Qt::Checked);
			else
				tagItem->setCheckState(Qt::Unchecked);

			// Insert Tag Item
			l.addItem(tagItem);
		}
		l.sortItems();
	}

	QObject::connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addTag()));
	QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(ok()));
	QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));

}

/********************************************************************
 *                              Getter                              *
 ********************************************************************/

const QStringList & TagsDialog::getSelectedTags() const{
	return m_selectedTags;
}

bool TagsDialog::isCancelled() const{
	return m_isCancelled;
}

/********************************************************************
 *                           Slot Method		                    *
 ********************************************************************/

void TagsDialog::addTag(){

	QString tag;
	bool ok;
	int begin = 0;

	QListWidget& l = *ui->tagsList;

	QRegExp rx("^[A-Z][a-z]{2,}$");
	QRegExpValidator val;
	val.setRegExp(rx);

	// Ask for new valide tag
	do{
		tag = QInputDialog::getText(this, "Create new Tag", "Tag (only use a-z characters) : ", QLineEdit::Normal, "", &ok).toLower();
		tag[0] = tag[0].toUpper();
	}while( ok &&  (val.validate(tag,begin) != QRegExpValidator::Acceptable || m_tagsList.contains(tag) ) );

	if(ok){

		// Create tag item
		QListWidgetItem* tagItem = new QListWidgetItem(tag, &l);
		tagItem->setFlags(tagItem->flags() | Qt::ItemIsUserCheckable);
		tagItem->setCheckState(Qt::Checked);

		// Add Tag to tag list
		m_tagsList << tag;

	}
}

void TagsDialog::ok(){
	// Set Selected Tags List
	QListWidget& l = *ui->tagsList;
	for(int i=0; i<l.count(); i++)
		if( l.item(i)->checkState() == Qt::Checked )
			m_selectedTags << l.item(i)->text();
	m_isCancelled = false;
	close();
}

/********************************************************************
 *                            Destructor                            *
 ********************************************************************/

TagsDialog::~TagsDialog()
{
	// Clear List View
	QListWidget& l = *ui->tagsList;
	QListWidgetItem* item = l.takeItem(0);
	while( item != NULL ){
		delete item;
		item = l.takeItem(0);
	}

	delete ui;
}
