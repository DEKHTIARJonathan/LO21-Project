#include <QApplication>
#include <QtGui>
#include <iostream>
#include "databasemanager.h"
#include "note.h"

using namespace std;

int main()
{
    databaseManager* db = new databaseManager("NoteDepot");

    std::cout<<"path:"<<db->getpath().toStdString()<<"\n";

    QString request0 = "create table Contacts (Name varchar(20), Mobile varchar(20),City varchar(30), primary key(Name, Mobile))";
    QString request1 = "INSERT INTO Contacts (Name, Mobile, City) VALUES ('John','0561390189', 'Toulouse')";
    QString request1_1 = "INSERT INTO Contacts (Name, Mobile, City) VALUES ('Johnny','0561390189', 'Toulouse')";

    if(db->query(request0))
        cout<<"ok";
    else
        cout<<"not ok";

    if(db->query(request1) && db->query(request1_1))
        cout<<"ok";
    else
        cout<<"not ok";

    cout<<endl;

    db->getPersonne();


    cout<<endl;cout<<endl;
}
