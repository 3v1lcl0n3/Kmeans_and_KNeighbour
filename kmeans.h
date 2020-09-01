#ifndef KMEANS_H
#define KMEANS_H

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

class KMeans {
public:
    KMeans();
    ~KMeans();
    double kMeansClustering(vector<Point>* points, int epochs, int k);
};

#endif
