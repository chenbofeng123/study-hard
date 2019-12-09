#ifndef BASICSTAT_H
#define BASICSTAT_H

#include <algorithm>
#include "graph.h"
#include "stat.h"

namespace snu {

	void basicStat(DSGraph& graph, StatResult& result);
	void basicStat(USGraph& graph, StatResult& result);
}

#endif // BASICSTAT_H
