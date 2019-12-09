#ifndef PLOT_H
#define PLOT_H

#include <string>


namespace snu {

    class Plot {
    public:
        std::string name;
        bool makeplot;

        Plot(std::string _name, bool _makeplot = false): name(_name), makeplot(_makeplot) {}
    };
}

#endif // PLOT_H

