#ifndef KMEANS_H
#define KMEANS_H

#include "pointvector.h"
#include <vector>
#include <ctime>

//using namespace std;

class KMeans {
public:
    KMeans();
    ~KMeans();
    double kMeansClustering(std::vector<Point>* points, int epochs, int k);
};

#endif
