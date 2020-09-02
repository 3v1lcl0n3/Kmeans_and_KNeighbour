#ifndef KNEAREST_H
#define KNEAREST_H

#include "pointvector.h"
#include <vector>
#include <algorithm>

class KNearest {
public:
    KNearest();
    ~KNearest();
    int classifyAPoint(std::vector<Point>* points, int k, int cluster_nr, Point unknown);
};

#endif
