#include "graph.h"


namespace snu {

    Graph::Graph() {}

    // destructor
    Graph::~Graph()
    {
        // delete vertex, edge, vertex_label, edge_label;
        for (auto it = id_to_vertex.begin(); it != id_to_vertex.end(); ++it) 
			delete it->second;
        for (auto it = id_to_edge.begin(); it != id_to_edge.end(); ++it) 
			delete it->second;
        for (auto it = vlabel_to_class.begin(); it != vlabel_to_class.end(); ++it) 
			delete it->second;
        for (auto it = elabel_to_class.begin(); it != elabel_to_class.end(); ++it) 
			delete it->second;
    }

    // do not have to define destructor of child classes

    // array version
    int Graph::addVertex(Vid id, long long num, Vlabel label[])
    {
        // error: graph already has a vertex having same id
        if (id_to_vertex.count(id)) return 1;

        Vertex *v = new Vertex();
        id_to_vertex[id] = v;
        v->id = id;

        // set labels
        // if no vertex label class then create it
        for (long long i = 0; i < num; ++i) {
            auto it = vlabel_to_class.find(label[i]);
            LabelOfVertices *vl;

            // no vertex label class
            if (it == vlabel_to_class.end()) {
                vl = new LabelOfVertices();
                vlabel_to_class[label[i]] = vl;
                vl->label = label[i];
            }
            else {
                vl = it->second;
            }
            
            vl->vertices.push_back(v);
            v->labels.push_back(vl);
        }

        return 0;
    }

    // vector version
    int Graph::addVertex(Vid id, std::vector <Vlabel> *label)
    {
        return addVertex(id, label->size(), label->data());
    }

    // base addEdge function, DSGraph version
    int Graph::addEdge(Eid id, long long num, Elabel label[], Vid from, Vid to, Weight weight) 
    {
        // error: already have edge having same id or no from or to vertex
        if (id_to_edge.count(id) || !id_to_vertex.count(from) || !id_to_vertex.count(to))
            return 1;

        Edge *e = new Edge();
        id_to_edge[id] = e;
        e->id = id;
        
        // set edge labels
        // if no edge label class then create it
        for (long long i = 0; i < num; ++i) {
            auto it = elabel_to_class.find(label[i]);
            LabelOfEdges *el;

            // no edge label class
            if (it == elabel_to_class.end()) {
                el = new LabelOfEdges();
                elabel_to_class[label[i]] = el;
                el->label = label[i];
            }
            else {
                el = it->second;
            }

            el->edges.push_back(e);
            e->labels.push_back(el);
        }

        e->from = id_to_vertex[from];
        e->to = id_to_vertex[to];
        e->to->indegree++;
        e->weight = weight;
        e->from->edges.push_back(e);
        
        is_connected.insert(std::make_pair(from, to));

        if (weight < 0) negative_edge_num++;

        return 0;
    }

    // array version
    int DSGraph::addEdge(Eid id, long long num, Elabel label[], Vid from, Vid to, Weight weight)
    {
        return Graph::addEdge(id, num, label, from, to, weight);
    }

    // vector version
    int DSGraph::addEdge(Eid id, std::vector <Elabel> *label, Vid from, Vid to, Weight weight)
    {
        return addEdge(id, label->size(), label->data(), from, to, weight);
    }

    // array version
    int USGraph::addEdge(Eid id, long long num, Elabel label[], Vid from, Vid to, Weight weight)
    {
        // there is an error
        if (Graph::addEdge(id, num, label, from, to, weight)) return 1;

        Edge *e = id_to_edge[id];
        e->to->edges.push_back(e);
        e->from->indegree++;
        is_connected.insert(std::make_pair(to, from));  // insert reverse
                                                        // be careful of switching from and to in this case

        return 0;
    }

    // vector version 
    int USGraph::addEdge(Eid id, std::vector <Elabel> *label, Vid from, Vid to, Weight weight)
    {
        return addEdge(id, label->size(), label->data(), from, to, weight);
    }
}

