#ifndef DRAW_CLUSTERS_H
#define DRAW_CLUSTERS_H

#include <vector>
#include "pointvector.h"

class Draw_Clusters {
public:
    Draw_Clusters ();
    ~Draw_Clusters ();
    int paint_up(int argc, char** argv, std::vector<Point>* points);
};


#endif
