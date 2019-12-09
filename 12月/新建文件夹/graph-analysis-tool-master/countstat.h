#ifndef COUNTSTAT_H
#define COINTSTAT_H

#include "graph.h"
#include "stat.h"

namespace snu {

	void countStat(USGraph& graph, StatResult& result);
	long long TriangleCount(std::vector<std::pair<long long, Graph::Vertex *> >& vec);
}

#endif // COUNTSTAT_H
