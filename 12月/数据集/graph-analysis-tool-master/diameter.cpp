#include "diameter.h"

#include <queue>


namespace snu {
    const unsigned long long INF = 0x7fffffffffffffff;

    typedef std::pair<bool, unsigned long long> info;
    inline bool visited(Graph::Vertex* vertex) { return static_cast<info*>(vertex->temp)->first; }
    inline unsigned long long distance(Graph::Vertex* vertex) { return static_cast<info*>(vertex->temp)->second; }

    inline unsigned long long max(unsigned long long x, unsigned long long y)
    {
        return (x > y) ? x : y;
    }

    // Given a node, returns a pair of the farthest node and its distance form the node.
    std::pair<Graph::Vertex*, unsigned long long> farthest(USGraph& graph, Graph::Vertex* root, bool init)
    {
        if (init) {
            for (auto id_vertex: graph.id_to_vertex) {
                Graph::Vertex* vertex = id_vertex.second;
                static_cast<info*>(vertex->temp)->first = false;
                static_cast<info*>(vertex->temp)->second = INF;
            }
        }

        std::queue<Graph::Vertex*> vertex_queue;

        static_cast<info*>(root->temp)->second = 0;
        vertex_queue.push(root);

        // Perform BFS and calculate distances to each node from the root node.
        while (!vertex_queue.empty()) {
            Graph::Vertex* curr = vertex_queue.front(); vertex_queue.pop();
            static_cast<info*>(curr->temp)->first = true;
            unsigned long long curr_dist = distance(curr);

            for (auto edge: curr->edges) {
                Graph::Vertex* next = (edge->to == curr) ? edge->from : edge->to;
                unsigned long long next_dist = distance(next);

                if (curr_dist + 1 < next_dist) {
                    static_cast<info*>(next->temp)->second = curr_dist + 1;
                    vertex_queue.push(next);
                }
            }
        }

        // Find the farthest node and its distance from the root node.
        Graph::Vertex* farthest_vertex = nullptr;
        unsigned long long farthest_dist = 0;
        for (auto id_vertex: graph.id_to_vertex) {
            Graph::Vertex* vertex = id_vertex.second;
            unsigned long long dist = distance(vertex);
            if (dist != INF && farthest_dist < dist) {
                farthest_dist = dist;
                farthest_vertex = vertex;
            }            
        }

        return std::make_pair(farthest_vertex, farthest_dist);
    }

    // Given a graph, returns the exact diameter of the graph.
    unsigned long long diameter(USGraph& graph)
    {
        for (auto id_vertex: graph.id_to_vertex) {
            Graph::Vertex* vertex = id_vertex.second;
            vertex->temp = new info(false, INF);
        }

        unsigned long long max_dist = 0;
        for (auto id_vertex: graph.id_to_vertex) {
            Graph::Vertex* vertex = id_vertex.second;

            // `farthest` returns a pair of the farthest node and its distance from the vertex.
            unsigned long long dist = farthest(graph, vertex).second;
            max_dist = max(dist, max_dist);
        }

        for (auto id_vertex: graph.id_to_vertex) {
            Graph::Vertex* vertex = id_vertex.second;
            delete static_cast<info*>(vertex->temp);
        }

        return max_dist;
    }

    // Given a graph, returns an approximate diameter of the graph.
    unsigned long long approximate_diameter(USGraph& graph)
    {
        for (auto id_vertex: graph.id_to_vertex) {
            Graph::Vertex* vertex = id_vertex.second;
            vertex->temp = new info(false, INF);
        }

        // Construct candidate set. 
        // Candidate set includes one node per connected component.
        std::set<Graph::Vertex*> candidate_nodes;
        for (auto id_vertex: graph.id_to_vertex) {
            Graph::Vertex* vertex = id_vertex.second;
            if (visited(vertex)) {
                continue;
            }
            candidate_nodes.insert(farthest(graph, vertex, false).first);
        }

        unsigned long long max_dist = 0;
        for (auto vertex: candidate_nodes) {
            unsigned long long dist = farthest(graph, vertex).second;
            max_dist = max(dist, max_dist);
        }

        for (auto id_vertex: graph.id_to_vertex) {
            Graph::Vertex* vertex = id_vertex.second;
            delete static_cast<info*>(vertex->temp);
        }

        // Return the distance between the node and the farthest node from the node.
        return max_dist;
    }
}

