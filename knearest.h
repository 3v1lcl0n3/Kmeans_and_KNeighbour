#ifndef KNEAREST_H
#define KNEAREST_H

#include "pointvector.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class KNearest {
public:
    KNearest();
    ~KNearest();
    int classifyAPoint(vector<Point>* points, int k, int cluster_nr, Point unknown);
};

#endif
