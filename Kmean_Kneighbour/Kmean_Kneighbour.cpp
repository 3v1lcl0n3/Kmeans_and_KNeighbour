// Kmean_Kneighbour.cpp : Defines the entry point for the application.
//

#include "Kmean_Kneighbour.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
	double x, y;     // koordinate
	int cluster;     // kluster kojemu pripada točka
	double minDist;  // minimalna udaljenost od klustera

	Point() : x(0.0), y(0.0), cluster(-1), minDist(DBL_MAX) {}
	Point(double x, double y) : x(x), y(y), cluster(-1), minDist(DBL_MAX) {}

	double distance(Point p) {
		return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y); // kvadrat udaljenosti do točke
	}
};

//funkcija za ispis vektora za debug
/*
void print(std::vector<double> const& input)
{
	for (int i = 0; i < input.size(); i++) {
		std::cout << input.at(i) << ' ';
	}
}
*/

//čitanje točaka iz .csv-a
vector<Point> readcsv() {
	vector<Point> points; //vektor točaka
	string line;
	ifstream file("mall_data.csv");

	while (getline(file, line)) {
		stringstream lineStream(line);
		string bit;
		double x, y;
		getline(lineStream, bit, ',');
		x = stof(bit);
		getline(lineStream, bit, '\n');
		y = stof(bit);

		points.push_back(Point(x, y)); // dodavanje točke u vektor
	}
	return points;
}

//zamjena dva člana vektora
void swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

// uzlazno sortiranje vektora po udaljenosti od nove točke za k-nearest neighbor
template<class T>
void Sort(std::vector<T>& a)
{
	for (unsigned i = 0; i < a.size(); ++i)
	{
		for (unsigned j = 0; j < (a.size() - i) - 1; ++j)
		{
			if (a[j].minDist > a[j + 1].minDist)
			{
				swap(a[j], a[j + 1]);
			}
		}
	}
}


//funkcija za k-means clustering
double kMeansClustering(vector<Point>* points, int epochs, int k) {
	int n = points->size();

	vector<Point> centroids; //vektor centroida
	srand(time(0));
	for (int i = 0; i < k; ++i) {
		centroids.push_back(points->at(rand() % n)); // nasumično daj broj svakoj centroidi
	}

	for (int i = 0; i < epochs; ++i) {
		//za svaku centroidu izračunaj udaljenost od točke i obnovi kluster točke
		for (vector<Point>::iterator c = begin(centroids); c != end(centroids); //iteriranje po vektoru ceontroida
			++c) {
			int clusterId = c - begin(centroids);

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

			it->minDist = DBL_MAX;  //resetira udaljenost
		}
		// računanje novih centroida,iterator po vektoru centroida
		for (vector<Point>::iterator c = begin(centroids); c != end(centroids);
			++c) {
			int clusterId = c - begin(centroids);
			c->x = sumX[clusterId] / nPoints[clusterId]; //pozicija na x ordinati za specificni centroid(suma X u nekom clusteru podijeljena s brojem točaka u clusteru)
			c->y = sumY[clusterId] / nPoints[clusterId]; //isto samo za y
		}


	}

	// ispis u .csv
	ofstream myfile;
	myfile.open("output.csv");
	myfile << "x,y,c" << endl;
	for (vector<Point>::iterator it = points->begin(); it != points->end();
		++it) {
		myfile << it->x << "," << it->y << "," << it->cluster << endl;
	}
	myfile.close();

	//AVG udaljenost od centroida, za računanje bodova za određeni broj clustera (elbow metoda)
	double mean_val = 0;
	//iterator po centroidima
	for (vector<Point>::iterator c = begin(centroids); c != end(centroids);
		++c) {
		int clusterId = c - begin(centroids);
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

//funkcija za k-nearest neighbor 
int classifyAPoint(vector<Point>* points, int k, int cluster_nr, Point unknown)
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
	Sort(*points);

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




int main() {
	vector<Point> points = readcsv();

	int cluster_test = 8;
	vector<double> arr(cluster_test);
	// pokrene K means algoritam podešeni broj puta da dobijemo optimalan broj za K elbow metodom
	for (int i = 1; i <= cluster_test; i++) {
		arr[i - 1] = kMeansClustering(&points, 100, i);
	}
	//ispis polja average udaljenosti od centroida za 1-8 K
	cout << "Average udaljenosti tocaka od svojih centroida: " << endl;
	for (int i = 0; i < cluster_test; i++) {
		cout << arr[i] << endl;
	}

	//najbolji broj klastera
	int best_cluster_number = 5;
	kMeansClustering(&points, 100, best_cluster_number);

	//točka koju želimo klasificirati za k nearest neighbor 
	Point unknown;
	unknown.x = 37;
	unknown.y = 65;
	// Parametar K govori koliko ćemo točaka oko odabrane uzeti u obzir za K nearest neighbor
	int k = 21;
	printf("Tocka na lokaciji %lf,%lf "" pripada clusteru %d.\n", unknown.x, unknown.y, classifyAPoint(&points, k, best_cluster_number, unknown));
	return 0;

}