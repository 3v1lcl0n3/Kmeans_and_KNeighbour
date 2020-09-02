#include "kmeans.h"
#include <iterator>

KMeans::KMeans(){}
KMeans::~KMeans(){}

double KMeans::kMeansClustering(std::vector<Point>* points, int epochs, int k) {
    int n = points->size();

    std::vector<Point> centroids; //vektor centroida
    centroids.clear();
    srand(time(0));
    for (int i = 0; i < k; ++i) {
        centroids.push_back(points->at(rand() % n)); // nasumično daj broj svakoj centroidi
    }

    for (int i = 0; i < epochs; ++i) {
        //za svaku centroidu izračunaj udaljenost od točke i obnovi kluster točke
        for (std::vector<Point>::iterator c = centroids.begin(); c != centroids.end(); //iteriranje po vektoru ceontroida
            ++c) {
            int clusterId = k - distance(c,centroids.end());
            //int clusterId = c - centroids.begin();
            //cout << clusterId << endl;
            for(Point& pt : *points){
                double dist = c->distance(pt); //udaljenost trenutnog centroida od točke
                if (dist < pt.minDist) { //ako je udaljenost manja od trenutne udaljenosti onda ->
                    pt.minDist = dist;  //postavi tu udaljenost na trenutnu
                    pt.cluster = clusterId; //  i obnovi Id clustera za tu točku
                }

            }
        }

        //dodatni vektori za računanje mean-a
        std::vector<int> nPoints;
        std::vector<double> sumX, sumY;
        //postavljanje inicijalnih vrijednosti
        for (int j = 0; j < k; ++j) {
            nPoints.push_back(0);
            sumX.push_back(0.0);
            sumY.push_back(0.0);
        }

        // iterirator po točkama da se dobiju podaci za račun pozicijecentroida
        for(Point& pt : *points) {
            int clusterId = pt.cluster; //pročitaj cluster točke
            nPoints[clusterId] += 1; //dodaj točku u specifički kluster
            sumX[clusterId] += pt.x; //povećaj sumu x-eva za određeni cluster
            sumY[clusterId] += pt.y; // povećaj sumu y

            pt.minDist = __DBL_MAX__;  //resetira udaljenost
        }

        // računanje novih centroida,iterator po vektoru centroida
        for (std::vector<Point>::iterator c = centroids.begin(); c != centroids.end();
            ++c) {
            int clusterId = k - distance(c,centroids.end());

            c->x = sumX[clusterId] / nPoints[clusterId]; //pozicija na x ordinati za specificni centroid(suma X u nekom clusteru podijeljena s brojem točaka u clusteru)
            c->y = sumY[clusterId] / nPoints[clusterId]; //isto samo za y
        }
    }

    //AVG udaljenost od centroida, za računanje bodova za određeni broj clustera (elbow metoda)
    double mean_val = 0;
    //iterator po centroidima
    for (std::vector<Point>::iterator c = centroids.begin(); c != centroids.end();
        ++c) {
        int clusterId = k - distance(c,centroids.end());
        //iterator po točkama
        for(Point& pt : *points) {
            //samo uzimaj uzimaju u obzir udaljenosti točaka od njihovih centroida
            if (pt.cluster == clusterId) {
                double dist = c->distance(pt);
                mean_val += dist;  // suma svih udaljenosti
            }
        }
    }
    mean_val /= n; //average svih udaljenosti

    return mean_val;
}
