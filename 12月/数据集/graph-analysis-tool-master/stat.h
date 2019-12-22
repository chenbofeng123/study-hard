#ifndef STAT_H
#define STAT_H

namespace snu {

	typedef struct StatResult {
		long long size; // number of vertices
		long long volume; // number of edges
		long long num_vlabel; // number of vertex label
		long long num_elabel; // number of edge label
		double density; // m / n^2, directed graph with loops
		double avg_degree; // average degree, 2m / n
		long long max_degree; // maximum degree
		long long max_indegree; // maximum indegree
		long long max_outdegree; // maximum outdegree
		// size of vertex label is defined as number of vertices having that label
		long long max_vlabel_size; // maximum size of vertex label
		long long max_elabel_size; // maximum size of edge label
		double reciprocity; // only defined in directed graph
		double negativity; // ratio of nagative edges

		// connectivity statistics 
		long long num_cc; // number of connected components
		long long num_scc; // number of strongly connected components
		long long num_wcc; // number of weakly connected components
		long long size_lcc; // largest size of connected components
		long long size_lscc; // largest size of strongly connected components
		long long size_lwcc; // largest size of weakly connected components
		long long diameter; // longest shortest paths

		// counting statistics 
		unsigned long long wedge_count; // number of wedges
		unsigned long long claw_count; // number of claws
		unsigned long long triangle_count; // number of triangles

		// statistic check
		bool basicstat = false;
		bool connectstat = false;
		bool countstat = false;
	} StatResult;

	void initStat(StatResult& result);
}

#endif // STAT_H
