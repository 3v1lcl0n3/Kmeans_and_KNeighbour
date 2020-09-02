#ifndef POINTVECTOR_H
#define POINTVECTOR_H

struct Point {
    double x, y;     // koordinate
    int cluster;     // kluster kojemu pripada točka
    double minDist;  // minimalna udaljenost od klustera

    Point() : x(0.0), y(0.0), cluster(-1), minDist(__DBL_MAX__) {}
    Point(double x, double y) : x(x), y(y), cluster(-1), minDist(__DBL_MAX__) {}

    double distance(Point p) {
        return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y); // kvadrat udaljenosti do točke
    }
};

#endif
