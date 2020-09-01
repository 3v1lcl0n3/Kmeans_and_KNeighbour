#ifndef CSVRW_H
#define CSVRW_H

#include <iostream>
#include <vector>
#include "pointvector.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>

class CsvRW {
public:
    CsvRW();
    ~CsvRW();
    std::vector<Point> readcsv();
    void writecsv(std::vector<Point> points);
};

#endif
