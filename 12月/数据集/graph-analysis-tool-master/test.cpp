#include <stdio.h>
#include <getopt.h>

#include <iostream>
#include <chrono>
#include <utility>

#include "graph.h"
#include "parse.h"
#include "diameter.h"


typedef std::chrono::milliseconds milliseconds;


void usage(void)
{
    printf(" usage: main <input file> [options]\n");
    printf("\n");
    printf("  options:\n");
    printf("   -d | --directed       set graph directed\n");
    printf("   -u | --undirected     set graph undirected (default)\n");
    printf("   -h | --help           print this list of help\n");
    printf("\n");
    printf("   e.g. ./main some_path/some_graph.snap --directed\n");

    return;
}


template<typename Ret, typename Func, typename ...Args>
milliseconds::rep measure(Ret&& ret, Func&& func, Args&&... args) {
    auto start = std::chrono::steady_clock::now();
    ret = std::forward<Func>(func)(std::forward<Args>(args)...);
    auto finish = std::chrono::steady_clock::now();

    return std::chrono::duration_cast<milliseconds>(finish - start).count();
}


int main(int argc, char* argv[]) 
{
    if (argc < 2) {
        usage();
        return 1;
    }

    bool directed = false;  // suppose given graph is undirected.

    while (true) {
        static struct option long_options[] = {
            {"directed", 0, NULL, 'd'}, 
            {"undirected", 0, NULL, 'u'}, 
            {"help", 0, NULL, 'h'}, 
            {0, 0, 0, 0}
        };

        int option = getopt_long(argc, argv, "duh", long_options, NULL);

        if (option < 0) {
            break;
        }

        switch (option) {
          case 'd':
            directed = true;
            break;

          case 'u':
            directed = false;
            break;

          case 'h':
            usage();
            return 0;

          default:
            usage();
            return 1;
        }
    }

    // There exists no non-option argument.
    // That is, input file path is not given.
    if (argc <= optind) {
        fprintf(stderr, "input file is not given.\n");
        return 1;
    }

    // Suppose input file path is the first non-option argument.
    std::string input_path(argv[optind]);

    // Extract name of given graph from input path.
    std::size_t slash = input_path.rfind("/");
    if (slash == std::string::npos) {
        slash = -1;
    }

    std::size_t dot = input_path.rfind(".");
    if (dot == std::string::npos) {
        dot = input_path.length();
    }

    std::string graph_name = input_path.substr(slash+1, dot-(slash+1));

    if (directed) {
        snu::DSGraph graph;
        int parse_status = snu::parseDSGraph(input_path, graph);
        switch (parse_status) {
          case snu::PARSE_SUCCESS:
            break;

          case snu::PARSE_FAILURE_NO_INPUT:
            fprintf(stderr, "input file is not locatable.\n");
            return 1;

          case snu::PARSE_FAILURE_INVALID_INPUT:
            fprintf(stderr, "input data is invalid.\n");
            return 1;

          case snu::PARSE_FAILURE_INVALID_FILETYPE:
            fprintf(stderr, "this filetype is not supported.\n");
            return 1;

          case snu::PARSE_FAILURE_ADD_VERTEX:
          case snu::PARSE_FAILURE_ADD_EDGE:
            fprintf(stderr, "internal error\n");
            return 1;

          default:
            return 1;
        }
    }
    else {
        snu::USGraph graph;
        int parse_status = snu::parseUSGraph(input_path, graph);
        switch (parse_status) {
          case snu::PARSE_SUCCESS:
            break;

          case snu::PARSE_FAILURE_NO_INPUT:
            fprintf(stderr, "input file is not locatable.\n");
            return 1;

          case snu::PARSE_FAILURE_INVALID_INPUT:
            fprintf(stderr, "input data is invalid.\n");
            return 1;

          case snu::PARSE_FAILURE_INVALID_FILETYPE:
            fprintf(stderr, "this filetype is not supported.\n");
            return 1;

          case snu::PARSE_FAILURE_ADD_VERTEX:
          case snu::PARSE_FAILURE_ADD_EDGE:
            fprintf(stderr, "internal error\n");
            return 1;

          default:
            return 1;
        }

        unsigned long long exact;
        milliseconds::rep exact_time = measure(exact, snu::diameter, graph);
        
        unsigned long long approx;
        milliseconds::rep approx_time = measure(approx, snu::approximate_diameter, graph);

        printf("exact diameter  : %10llu (%10ld ms)\n", exact, exact_time);
        printf("approx. diameter: %10llu (%10ld ms)\n", approx, approx_time);
    }
	
	return 0;
}


