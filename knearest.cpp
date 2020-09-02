#include "knearest.h"
#include "pointvector.h"


KNearest::KNearest(){}
KNearest::~KNearest(){}

double comparison(Point a, Point b){

    return a.minDist < b.minDist;

}

//funkcija za k-nearest neighbor
int KNearest::classifyAPoint(vector<Point>* points, int k, int cluster_nr, Point unknown)
{
    //int n = points->size();
    //napuni vektor s sa svim točkama i udaljenosti od nove točke

    for(Point& pt : *points){
        double dist = pt.distance(unknown);
        pt.minDist = dist;
    }

    //funkcija za sortiranje točaka od najmanje do najveće udaljenosti od nove točke
    sort(points->begin(),points->end(),comparison);

    vector<int> freq(k);

    //puni vektor frekvencija ovisno o K, tako da broji frekvencije K nabližih točaka od tražene
    int counter = 0;
    for(Point& pt : *points){
        if (counter == k) break;
        int pos = pt.cluster;
        freq[pos]++;
        counter++;
    }

    int max = 0;
    int maxid = -1;

    //nalazi max vrijednost pojava neke od frekvencija, sto govori kojem clusteru pripada točka
    for (int i = 0; i < cluster_nr; ++i) {
        //cout << freq[i] << endl;
        if (freq[i] > max) {
            max = freq[i];
            maxid = i;
        }
    }

    return maxid;
}
