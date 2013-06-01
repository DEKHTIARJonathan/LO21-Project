#ifndef STRATEGIES_H
#define STRATEGIES_H

#include <QStringBuilder>
#include <export/exportstrategy.h>

template<class typeNote>
class Strategies
{
	public:
		virtual QString	exportNote( const ExportStrategy& es) const{
			return	typeNote::staticMetaObject.className() %
					es.header() %
					es.exportNote( (typeNote&) *this ) %
					es.footer();
		}
};

#endif // STRATEGIES_H
