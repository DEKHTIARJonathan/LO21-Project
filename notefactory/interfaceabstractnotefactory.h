#ifndef INTERFACEABSTRACTNOTEFACTORY_H
#define INTERFACEABSTRACTNOTEFACTORY_H

class InterfaceAbstractNoteFactory
{
	public:
		virtual void			constructStorage() = 0;

	protected:
		virtual unsigned int	allocPart() = 0;
		//virtual void			fillSpecificPart(Note& n);
};

#endif // INTERFACEABSTRACTNOTEFACTORY_H
