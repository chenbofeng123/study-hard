#ifndef DIAMETER_H
#define DIAMETER_H

#include <set>
#include <utility>

#include "graph.h"

namespace snu {
    // Given a graph and a node, returns the farthest node and its distance from the node.
    std::pair<Graph::Vertex*, unsigned long long> farthest(USGraph& graph, Graph::Vertex* root, bool init = true);

    // Given a graph, returns the exact diameter of the graph.
    unsigned long long diameter(USGraph& graph);

    // Given a graph, returns an approximate diameter of the graph.
    unsigned long long approximate_diameter(USGraph& graph);
}

#endif

