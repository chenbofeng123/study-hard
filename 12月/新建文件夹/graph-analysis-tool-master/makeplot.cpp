#include "makeplot.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>


namespace snu {

    void makePlot(DSGraph& graph, Plot& plot)
    {
        std::ofstream out;

        // label-vertex
        out.open("./pyplot/label-vertex.txt");

        long long n = graph.id_to_vertex.size();
        typedef std::pair<std::string*, long long> label_vertex;
        std::vector<label_vertex> lv;
        lv.reserve(n);
        for (auto it = graph.vlabel_to_class.begin(); it != graph.vlabel_to_class.end(); ++it) {
            auto vlabel = it->second;
            lv.push_back(make_pair(&(vlabel->label), vlabel->vertices.size()));
        }

        std::sort(lv.begin(), lv.end(), [](label_vertex a, label_vertex b) { return a.second > b.second; });

        for (auto it = lv.begin(); it != lv.end(); ++it)
            out << *(it->first) << " " << it->second << std::endl;

        out.close();

        std::string cmd = "python label-vertex.py " + plot.name;
        system(cmd.c_str());

        // indegree
        out.open("./pyplot/indegree.txt");

        std::vector<long long> degree;
        degree.reserve(n);
        for (auto it = graph.id_to_vertex.begin(); it != graph.id_to_vertex.end(); ++it)
            degree.push_back((*it->second).indegree);
        
        std::sort(degree.begin(), degree.end());
        for (auto it = degree.begin(); it != degree.end(); ++it)
            out << *it << " ";

        out.close();

        cmd = "python indegree.py " + plot.name;
        system(cmd.c_str());

        // outdegree
        out.open("./pyplot/outdegree.txt");

        degree.clear();
        degree.reserve(n);
        for (auto it = graph.id_to_vertex.begin(); it != graph.id_to_vertex.end(); ++it)
            degree.push_back((*it->second).edges.size());
        
        std::sort(degree.begin(), degree.end());
        for (auto it = degree.begin(); it != degree.end(); ++it)
            out << *it << " ";

        out.close();

        cmd = "python outdegree.py " + plot.name;
        system(cmd.c_str());

        plot.makeplot = true;
    }

    void makePlot(USGraph& graph, Plot& plot)
    {
        std::ofstream out;

        // label-vertex
        out.open("./pyplot/label-vertex.txt");

        long long n = graph.id_to_vertex.size();
        typedef std::pair<std::string*, long long> label_vertex;
        std::vector<label_vertex> lv;
        lv.reserve(n);
        for (auto it = graph.vlabel_to_class.begin(); it != graph.vlabel_to_class.end(); ++it) {
            auto vlabel = it->second;
            lv.push_back(make_pair(&(vlabel->label), vlabel->vertices.size()));
        }

        std::sort(lv.begin(), lv.end(), [](label_vertex a, label_vertex b) { return a.second > b.second; });

        for (auto it = lv.begin(); it != lv.end(); ++it)
            out << *(it->first) << " " << it->second << std::endl;

        out.close();
        
        std::string cmd = "python label-vertex.py " + plot.name;
        system(cmd.c_str());

        // degree
        out.open("./pyplot/degree.txt");

        std::vector <long long> degree;
        degree.reserve(n);
        for (auto it = graph.id_to_vertex.begin(); it != graph.id_to_vertex.end(); ++it)
            degree.push_back((*it->second).indegree);
        
        std::sort(degree.begin(), degree.end());
        for (auto it = degree.begin(); it != degree.end(); ++it)
            out << *it << " ";

        out.close();

        cmd = "python degree.py " + plot.name;
        system(cmd.c_str());

        // pyplot
        plot.makeplot = true;
    }
}

