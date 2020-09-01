#include "knearest.h"

KNearest::KNearest(){}
KNearest::~KNearest(){}

double comparison(Point a, Point b){

    return a.minDist < b.minDist;

}


//funkcija za k-nearest neighbor
int KNearest::classifyAPoint(vector<Point>* points, int k, int cluster_nr, Point unknown)
{
    int n = points->size();
    //napuni vektor s sa svim točkama i udaljenosti od nove točke
    for (vector<Point>::iterator it = points->begin();
        it != points->end(); ++it) {
        Point p = *it;
        double dist = p.distance(unknown);
        p.minDist = dist;
        *it = p;
    }

    //funkcija za sortiranje točaka od najmanje do najveće udaljenosti od nove točke
    //Sort(*points);

    sort(points->begin(),points->end(),comparison);

    vector<int> freq(k);

    //puni vektor frekvencija ovisno o K, tako da broji frekvencije K nabližih točaka od tražene
    int counter = 0;
    for (vector<Point>::iterator it = points->begin();
        it != points->end(); ++it) {

        if (counter == k) break;
        int pos = it->cluster;
        freq[pos]++;
        counter++;

    }

    int max = 0;
    int maxid = -1;

    //nalazi max vrijednost pokava neke od frekvencija, sto govori kojem clusteru pripada točka
    for (int i = 0; i < cluster_nr; i++) {
        //cout << freq[i] << endl;
        if (freq[i] > max) {
            max = freq[i];
            maxid = i;
        }
    }
    return maxid;
}
