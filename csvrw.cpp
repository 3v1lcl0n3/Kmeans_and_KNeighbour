#include "csvrw.h"

CsvRW::CsvRW(){}
CsvRW::~CsvRW(){}

//čitanje točaka iz .csv-a
std::vector<Point> CsvRW::readcsv() {
    std::vector<Point> points; //vektor točaka
    std::string line;
    std::ifstream file("mall_data.csv");

    while (getline(file, line)) {
        std::stringstream lineStream(line);
        std::string bit;
        double x, y;
        std::getline(lineStream, bit, ',');
        x = stof(bit);
        std::getline(lineStream, bit, '\n');
        y = stof(bit);

        points.push_back(Point(x, y)); // dodavanje točke u vektor
    }
    return points;
}



void CsvRW::writecsv(std::vector<Point> points) {

    std::ofstream myfile;
    myfile.open("output.csv");
    myfile << "x,y,c" << std::endl;
    for (std::vector<Point>::iterator it = points.begin(); it != points.end();
        ++it) {
        myfile << it->x << "," << it->y << "," << it->cluster << std::endl;
    }
    myfile.close();

}
