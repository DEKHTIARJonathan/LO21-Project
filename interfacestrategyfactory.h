#ifndef INTERFACESTRATEGYFACTORY_H
#define INTERFACESTRATEGYFACTORY_H

#include <note/note.h>

template<typename ReturnType, typename Strategy>
class InterfaceStrategyFactory
{
	public:
		virtual ReturnType apply(Strategy& stra, Note& n) = 0;
};

#endif // INTERFACESTRATEGYFACTORY_H
