#include "basicstat.h"

namespace snu {

	void basicStat(DSGraph& graph, StatResult& result) {
		long long n = graph.id_to_vertex.size();
		long long m = graph.id_to_edge.size();

		result.size = n;
		result.volume = m;
		result.num_vlabel = graph.vlabel_to_class.size();
		result.num_elabel = graph.elabel_to_class.size();
		result.density = (double) m / (n * n); // assume there is loop

		long long max_indegree = 0;
		long long max_outdegree = 0;
		for(auto it = graph.id_to_vertex.begin(); it != graph.id_to_vertex.end(); it++) {
			max_indegree = std::max(max_indegree, it->second->indegree);
			max_outdegree = std::max(max_outdegree, (long long)it->second->edges.size());
		}
		result.max_indegree = max_indegree;
		result.max_outdegree = max_outdegree;
		
		long long max_vlabel_size = 0;
		for(auto it = graph.vlabel_to_class.begin(); it != graph.vlabel_to_class.end(); it++)
			max_vlabel_size = std::max(max_vlabel_size, (long long)it->second->vertices.size());
		result.max_vlabel_size = max_vlabel_size;

		long long max_elabel_size = 0;
		for(auto it = graph.elabel_to_class.begin(); it != graph.elabel_to_class.end(); it++)
			max_elabel_size = std::max(max_elabel_size, (long long)it->second->edges.size());
		result.max_elabel_size = max_elabel_size;

		long long cycle_count = 0;
		for(auto it = graph.id_to_edge.begin(); it != graph.id_to_edge.end(); it++) {
			Graph::Vid from = it->second->from->id;
			Graph::Vid to = it->second->to->id;
			if(graph.is_connected.count(std::make_pair(to, from))) 
				cycle_count++;
		}
		result.reciprocity = (double) cycle_count / m;

		result.negativity = (double) graph.negative_edge_num / m;

		result.basicstat = true;
	}

	void basicStat(USGraph& graph, StatResult& result) {
		long long n = graph.id_to_vertex.size();
		long long m = graph.id_to_edge.size();

		result.size = n; // n
		result.volume = m; // m
		result.num_vlabel = graph.vlabel_to_class.size();
		result.num_elabel = graph.elabel_to_class.size();
		result.density = 2.0 * m / (n * (n + 1)); // assume there is loop
		result.avg_degree = 2.0 * m / n; // 2 * m / n
		
		long long max_degree = 0;
		for(auto it = graph.id_to_vertex.begin(); it != graph.id_to_vertex.end(); it++)
			max_degree = std::max(max_degree, it->second->indegree); // indegree == outdegree
		result.max_degree = max_degree;

		long long max_vlabel_size = 0;
		for(auto it = graph.vlabel_to_class.begin(); it != graph.vlabel_to_class.end(); it++)
			max_vlabel_size = std::max(max_vlabel_size, (long long)it->second->vertices.size());
		result.max_vlabel_size = max_vlabel_size;

		long long max_elabel_size = 0;
		for(auto it = graph.elabel_to_class.begin(); it != graph.elabel_to_class.end(); it++)
			max_elabel_size = std::max(max_elabel_size, (long long)it->second->edges.size());
		result.max_elabel_size = max_elabel_size;

		result.negativity = (double) graph.negative_edge_num / m;

		result.basicstat = true;
	}
}
