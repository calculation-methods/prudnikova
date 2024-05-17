#ifndef PRINTFILE_H
#define PRINTFILE_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "structures.h"
#include "readfile.h"

void printTableFunctionToFile(const TableFunction& f);

void writeParameters(const Parameters& params, const std::string& filename);

#endif