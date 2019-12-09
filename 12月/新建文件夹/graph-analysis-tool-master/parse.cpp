#include <fstream>
#include <sstream>
#include <algorithm>
#include "parse.h"


namespace snu {

    // parse .snu file
    int parseDSGraphSNU(std::string file_path, DSGraph& graph)
    {
        std::ifstream infile(file_path);
        if (infile.fail()) {
            return PARSE_FAILURE_NO_INPUT;
        }

        std::string line;
        Graph::Eid eid = 0;

        while (getline(infile, line)) {
            std::istringstream iss(line);

            std::string sign;
            iss >> sign;
            
            if (sign == "t") {}
            else if (sign == "v") {
                Graph::Vid id;
                Graph::Vlabel label;
                std::vector <Graph::Vlabel> label_vector;

                iss >> id;
                while (iss >> label) {
                    label_vector.push_back(label);
                }

                if (graph.addVertex(id, &label_vector)) {
                    return PARSE_FAILURE_ADD_VERTEX;
                }
            }
            else if (sign == "e") {
                Graph::Vid from, to;
                Graph::Elabel label;
                std::vector<Graph::Elabel> label_vector;

                iss >> from >> to;
                while (iss >> label) {
                    label_vector.push_back(label);
                }

                if (graph.addEdge(eid, &label_vector, from, to, 1)) {
                    return PARSE_FAILURE_ADD_EDGE;
                }
                ++eid;
            }
            else {
                return PARSE_FAILURE_INVALID_INPUT;
            }
        }

        return PARSE_SUCCESS;
    }

    // parse .net file
    int parseDSGraphNET(std::string file_path, DSGraph& graph) 
    {
        std::ifstream infile(file_path);
        if (infile.fail()) {
            return PARSE_FAILURE_NO_INPUT;
        }

        std::string line;
        bool check_vertex = false;
        bool check_edge = false;

        while (getline(infile, line)) {
            std::istringstream iss(line);

            if (line.find("*Vertices") != std::string::npos || line.find("*vertices") != std::string::npos) {
                check_vertex = true;
                check_edge = false;
                continue;
            }
            else if (line.find("*arcs") != std::string::npos || line.find("*Arcs") != std::string::npos) {
                check_edge = true;
                check_vertex = false;
                continue;
            }

            if (check_vertex) {
                Graph::Vid id;
                std::vector <Graph::Vlabel> label_vector;
                Graph::Vlabel label;
                iss >> id;

                while (iss >> label) {
                    label.erase(std::remove(label.begin(), label.end(), '\"'), label.end());
                    label_vector.push_back(label);
                }

                if (graph.addVertex(id, &label_vector)) {
                    return PARSE_FAILURE_ADD_VERTEX;
                }
            }

            if (check_edge) {
                Graph::Eid id;
                Graph::Vid from;
                Graph::Vid to;
                std::vector <Graph::Elabel> label_vector;
                Graph::Elabel label;

                iss >> id >> from >> to;
                while (iss >> label) {
                    if (label == "l") continue;
                    label.erase(std::remove(label.begin(), label.end(), '\"'), label.end());
                    label_vector.push_back(label);
                }

                if (graph.addEdge(id, &label_vector, from, to, 1)) {
                    return PARSE_FAILURE_ADD_EDGE;
                }
            }
        }

        return PARSE_SUCCESS;
    }

    // parse .snap file
    int parseDSGraphSNAP(std::string file_path, DSGraph& graph)
    {
        std::ifstream infile(file_path);
        if (infile.fail()) {
            return PARSE_FAILURE_NO_INPUT;
        }

        std::string line;
        std::unordered_set <int> set;
        Graph::Eid eid = 0;

        while (getline(infile, line)) {
            std::istringstream iss(line);

            if (line.find("#") != std::string::npos)
                continue;

            Graph::Vid from, to;
            iss >> from >> to;

            if (!set.count(from)) {
                set.insert(from);
                if (graph.addVertex(from, 0, NULL)) {
                    return PARSE_FAILURE_ADD_VERTEX;
                }
            }

            if (!set.count(to)) {
                set.insert(to);
                if (graph.addVertex(to, 0, NULL)) {
                    return PARSE_FAILURE_ADD_VERTEX;
                }
            }

            if (graph.addEdge(eid, 0, NULL, from, to, 1)) {
                return PARSE_FAILURE_ADD_EDGE;
            }
            ++eid;
        }

        return PARSE_SUCCESS;
    }

    // parsing DSGraph version follows
    int parseDSGraph(std::string file_path, DSGraph& graph)
    {
        if (file_path.rfind(".snu") == file_path.length() - 4)
            return parseDSGraphSNU(file_path, graph);
        else if (file_path.rfind(".snap") == file_path.length() - 5)
            return parseDSGraphSNAP(file_path, graph);
        else if (file_path.rfind(".net") == file_path.length() - 4)
            return parseDSGraphNET(file_path, graph);

        return PARSE_FAILURE_INVALID_FILETYPE;
    }

    int parseUSGraphSNU(std::string file_path, USGraph& graph)
    {
        std::ifstream infile(file_path);
        if (infile.fail()) {
            return PARSE_FAILURE_NO_INPUT;
        }

        std::string line;
        Graph::Eid eid = 0;

        while (getline(infile, line)) {
            std::istringstream iss(line);

            std::string sign;
            iss >> sign;
            if (sign == "t") {}
            else if (sign == "v") {
                Graph::Vid id;
                Graph::Vlabel label;
                std::vector<Graph::Vlabel> label_vector;

                iss >> id;
                while (iss >> label) {
                    label_vector.push_back(label);
                }

                if (graph.addVertex(id, &label_vector)) {
                    return PARSE_FAILURE_ADD_VERTEX;
                }
            }
            else if (sign == "e") {
                Graph::Vid from, to;
                Graph::Elabel label;
                std::vector<Graph::Elabel> label_vector;

                iss >> from >> to;
                while (iss >> label) {
                    label_vector.push_back(label);
                }

                if (graph.addEdge(eid, &label_vector, from, to, 1)) {
                    return PARSE_FAILURE_ADD_EDGE;
                }
                ++eid;
            }
            else {
                return PARSE_FAILURE_INVALID_INPUT;
            }
        }

        return PARSE_SUCCESS;
    }

    int parseUSGraphSNAP(std::string file_path, USGraph& graph)
    {
        std::ifstream infile(file_path);
        if (infile.fail()) {
            return PARSE_FAILURE_NO_INPUT;
        }

        std::string line;
        std::unordered_set<int> set;
        Graph::Eid eid = 0;

        while (getline(infile, line)) {
            std::istringstream iss(line);

            if (line.find("#") != std::string::npos) {
                continue;
            }

            Graph::Vid from, to;
            iss >> from >> to;

            if (!set.count(from)) {
                set.insert(from);
                if (graph.addVertex(from, 0, NULL)) {
                    return PARSE_FAILURE_ADD_VERTEX;
                }
            }

            if (!set.count(to)) {
                set.insert(to);
                if (graph.addVertex(to, 0, NULL)) {
                    return PARSE_FAILURE_ADD_VERTEX;
                }
            }

            if (graph.addEdge(eid, 0, NULL, from, to, 1)) {
                return PARSE_FAILURE_ADD_EDGE;
            }
            ++eid;
        }

        return PARSE_SUCCESS;
    }

    int parseUSGraph(std::string file_path, USGraph& graph)
    {
        if (file_path.rfind(".snu") == file_path.length() - 4)
            return parseUSGraphSNU(file_path, graph);
        else if (file_path.rfind(".snap") == file_path.length() - 5)
            return parseUSGraphSNAP(file_path, graph);
        else if (file_path.rfind(".net") == file_path.length() - 4)
            return PARSE_FAILURE_INVALID_FILETYPE;

        return PARSE_FAILURE_INVALID_FILETYPE;
    }
}

