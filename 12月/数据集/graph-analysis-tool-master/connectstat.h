#ifndef CONNECTSTAT_H
#define CONNECTSTAT_H

#include <algorithm>
#include "graph.h"
#include "stat.h"

namespace snu {

	void connectStat(DSGraph& graph, StatResult& result);
	void connectStat(USGraph& graph, StatResult& result);
}

#endif // CONNECTSTAT_H
