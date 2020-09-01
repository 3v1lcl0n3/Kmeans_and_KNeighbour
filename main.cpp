#include "csvrw.h"
#include "pointvector.h"
#include "kmeans.h"
#include "knearest.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {

    CsvRW csv_handler;
    vector<Point> points = csv_handler.readcsv();

    int cluster_test = 8;
    vector<double> arr(cluster_test);

    KMeans KMalg;
    // pokrene K means algoritam podešeni broj puta da dobijemo optimalan broj za K elbow metodom
    for (int i = 1; i <= cluster_test; i++) {
        arr[i - 1] = KMalg.kMeansClustering(&points, 100, i);
    }

    //ispis polja average udaljenosti od centroida za 1-8 K
    cout << "Average udaljenosti tocaka od svojih centroida: " << endl;
    for (int i = 0; i < cluster_test; i++) {
        cout << arr[i] << endl;
    }

    //najbolji broj klastera
    int best_cluster_number = 5;
    KMalg.kMeansClustering(&points, 100, best_cluster_number);

    // ispis u .csv
    csv_handler.writecsv(points);

    //točka koju želimo klasificirati za k nearest neighbor
    Point unknown;
    unknown.x = 37;
    unknown.y = 65;
    // Parametar K govori koliko ćemo točaka oko odabrane uzeti u obzir za K nearest neighbor
    KNearest KNalg;

    int k = 21;
    printf("Tocka na lokaciji %lf,%lf "" pripada clusteru %d.\n", unknown.x, unknown.y, KNalg.classifyAPoint(&points, k, best_cluster_number, unknown)); //3. DIO K MEANS NEIGHBOR
    return 0;

}
