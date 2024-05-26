#ifndef READFILE_H
#define READFILE_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#include "structures.h"

struct Parameters {
    table_function f, u, v;
    double T, steps, delta_x, delta_y, delta_t;
};

Parameters readParameters(const std::string& filename);

std::vector<table_function> readMatrices(std::istream& stream);

#endif