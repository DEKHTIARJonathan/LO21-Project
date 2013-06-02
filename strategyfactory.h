#ifndef STRATEGYFACTORY_H
#define STRATEGYFACTORY_H

#include <interfacestrategyfactory.h>

template<typename ReturnType, typename Strategy, class NoteType>
class StrategyFactory : InterfaceStrategyFactory<ReturnType,Strategy>
{
	public:
		ReturnType apply(Strategy& stra, Note& n){
			NoteType& casted_n = dynamic_cast<NoteType&> (n);
			return stra(casted_n);
		}
};

#endif // STRATEGYFACTORY_H
