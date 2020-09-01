#include "kmeans.h"

KMeans::KMeans(){}
KMeans::~KMeans(){}

double KMeans::kMeansClustering(vector<Point>* points, int epochs, int k) {
    int n = points->size();

    vector<Point> centroids; //vektor centroida
    srand(time(0));
    for (int i = 0; i < k; ++i) {
        centroids.push_back(points->at(rand() % n)); // nasumično daj broj svakoj centroidi
    }

    for (int i = 0; i < epochs; ++i) {
        //za svaku centroidu izračunaj udaljenost od točke i obnovi kluster točke
        for (vector<Point>::iterator c = centroids.begin(); c != centroids.end(); //iteriranje po vektoru ceontroida
            ++c) {
            int clusterId = c - centroids.begin();

            for (vector<Point>::iterator it = points->begin(); //iteriranje po vektoru točaka
                it != points->end(); ++it) {
                Point p = *it;
                double dist = c->distance(p); //udaljenost trenutnog centroida od točke
                if (dist < p.minDist) { //ako je udaljenost manja od trenutne udaljenosti onda ->
                    p.minDist = dist;  //postavi tu udaljenost na trenutnu
                    p.cluster = clusterId; //  i obnovi Id clustera za tu točku

                }
                *it = p;
            }
        }

        //dodatni vektori za računanje mean-a
        vector<int> nPoints;
        vector<double> sumX, sumY;
        //postavljanje inicijalnih vrijednosti
        for (int j = 0; j < k; ++j) {
            nPoints.push_back(0);
            sumX.push_back(0.0);
            sumY.push_back(0.0);
        }

        // iterirator po točkama da se dobiju podaci za račun pozicijecentroida
        for (vector<Point>::iterator it = points->begin(); it != points->end();
            ++it) {
            int clusterId = it->cluster; //pročitaj cluster točke
            nPoints[clusterId] += 1; //dodaj točku u specifički kluster
            sumX[clusterId] += it->x; //povećaj sumu x-eva za određeni cluster
            sumY[clusterId] += it->y; // povećaj sumu y

            it->minDist = __DBL_MAX__;  //resetira udaljenost
        }
        // računanje novih centroida,iterator po vektoru centroida
        for (vector<Point>::iterator c = centroids.begin(); c != centroids.end();
            ++c) {
            int clusterId = c - centroids.begin();
            c->x = sumX[clusterId] / nPoints[clusterId]; //pozicija na x ordinati za specificni centroid(suma X u nekom clusteru podijeljena s brojem točaka u clusteru)
            c->y = sumY[clusterId] / nPoints[clusterId]; //isto samo za y
        }


    }



    //AVG udaljenost od centroida, za računanje bodova za određeni broj clustera (elbow metoda)
    double mean_val = 0;
    //iterator po centroidima
    for (vector<Point>::iterator c = centroids.begin(); c != centroids.end();
        ++c) {
        int clusterId = c - centroids.begin();
        //iterator po točkama
        for (vector<Point>::iterator it = points->begin();
            it != points->end(); ++it) {
            Point p = *it;
            //samo uzimaj uzimaju u obzir udaljenosti točaka od njihovih centroida
            if (p.cluster == clusterId) {
                double dist = c->distance(p);
                mean_val += dist;  // suma svih udaljenosti
            }
            *it = p;
        }
    }
    mean_val /= n; //average svih udaljenosti

    return mean_val;
}
