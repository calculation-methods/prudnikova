#ifndef READFILE_H
#define READFILE_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "structures.h"

std::vector<TableFunction> readMatrices(const std::string& filename);

#endif