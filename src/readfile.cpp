#include "readfile.h"

std::vector<TableFunction> readMatrices(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<TableFunction> functions;

    if (file.is_open()) {
        std::string line;
        TableFunction newFunction;
        bool newMatrixStarted = false;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::vector<double> row;
            double value;

            while (iss >> value) {
                row.push_back(value);
            }

            if (!row.empty()) {
                newFunction.points.push_back(row);
                row.clear();
                newMatrixStarted = true;
            } else if (newMatrixStarted) {
                if (!newFunction.points.empty()) {
                    functions.push_back(newFunction);
                    newFunction.points.clear();
                }
                newMatrixStarted = false;
            }
        }

        if (!newFunction.points.empty()) {
            functions.push_back(newFunction);
        }

        file.close();
    } else {
        throw std::ios_base::failure("Ошибка чтения файла .txt");
    }

    return functions;
}
