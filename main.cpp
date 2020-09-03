#include "csvrw.h"
#include "pointvector.h"
#include "kmeans.h"
#include "knearest.h"
#include "draw_clusters.h"

int main(int iArgc, char** cppArgv) {


    CsvRW csv_handler;
    KMeans KMalg;
    KNearest KNalg;
    std::vector<Point> points = csv_handler.readcsv();
    int cluster_test = 8; // broj clustera od 1 do zadanog broja za koje ćemo testirati dataset
    int k = 21; // Parametar K govori koliko ćemo točaka oko odabrane uzeti u obzir za K nearest neighbor

    // pokrene K means algoritam podešeni broj puta da dobijemo optimalan broj za K elbow metodom
    //ispis polja average udaljenosti od centroida za 1-8 K
    for (int i = 1; i <= cluster_test; i++) {
        std::cout << KMalg.kMeansClustering(&points, 100, i) << std::endl;
    }

    //najbolji broj klastera
    int best_cluster_number = 5;
    KMalg.kMeansClustering(&points, 100, best_cluster_number);

    //grafički prikaz, treba ga još malo uredit u bolje ukomponirat
    Draw_Clusters draw;
    draw.paint_up(iArgc, cppArgv,&points);

    // ispis u .csv
    csv_handler.writecsv(points);

    //točka koju želimo klasificirati za k nearest neighbor
    Point unknown;
    unknown.x = 37;
    unknown.y = 65;

    printf("Tocka na lokaciji %.0lf,%.0lf "" pripada clusteru %d.\n", unknown.x, unknown.y, KNalg.classifyAPoint(&points, k, best_cluster_number, unknown)); //3. DIO K MEANS NEIGHBOR
    return 0;

}
