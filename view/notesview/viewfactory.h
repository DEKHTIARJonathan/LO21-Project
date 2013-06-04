#ifndef VIEWFACTORY_H
#define VIEWFACTORY_H

#include <view/notesview/interfaceviewfactory.h>

template<class NoteType, class ViewType>
class ViewFactory : public InterfaceViewFactory
{
	public:
		NoteView& buildNoteView(Note& n){
			NoteType& casted_n = dynamic_cast<NoteType&> (n);

			return *( new ViewType(casted_n) );
		}
};

#endif // VIEWFACTORY_H
