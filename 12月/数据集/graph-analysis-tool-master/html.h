#ifndef HTML_H
#define HTML_H

#include "stat.h"
#include "plot.h"


namespace snu {

    void makeDSHtml(const char *name, StatResult& result, Plot& plot);
    void makeUSHtml(const char *name, StatResult& result, Plot& plot);
}

#endif // HTML_H

