#include "operations.h"

// df/dx в точке
double df_dx(const TableFunction& f, const Grid& g, int i, int j) {
    if (i < 0 || i >= f.points.size()) {
        return 0;
    }
    if (j < 0 || j >= f.points[i].size()) {
        return 0;
    }
    if (i == 0) {
        // Для первой и последней точек используем односторонние разности
        return (f.points[i + 1][j] - f.points[i][j]) / g.delta_x;
    }
    if (i == static_cast<int>(f.points.size()) - 1) {
        return (f.points[i][j] - f.points[i - 1][j]) / g.delta_x;
    }    
    // Для остальных точек используем центральную разность
    return (f.points[i + 1][j] - f.points[i - 1][j]) / (2.0 * g.delta_x);
}


// df/dy в точке
double df_dy(const TableFunction& f, const Grid& g, int i, int j) {
    if (i < 0 || i >= f.points.size()) {
        return 0;
    }
    if (j < 0 || j >= f.points[i].size()) {
        return 0;
    }
    if (j == 0) {
        // Для первой и последней точек используем односторонние разности
        return (f.points[i][j + 1] - f.points[i][j]) / g.delta_y;
    } else if (j == static_cast<int>(f.points[i].size()) - 1) {
        return (f.points[i][j] - f.points[i][j - 1]) / g.delta_y;
    } else {
        // Для остальных точек используем центральную разность
        return (f.points[i][j + 1] - f.points[i][j - 1]) / (2 * g.delta_y);
    }
}


// df/dx с результатами на плоскости
TableFunction df_dx_(const TableFunction& f, const Grid& g) {
    TableFunction result;
    result.points.resize(f.points.size());

    for (size_t i = 0; i < f.points.size(); i++) {
        for (size_t j = 0; j < f.points[i].size(); j++) {
            result.points[i][j] = df_dx(f, g, static_cast<int>(i), static_cast<int>(j));
        }
    }

    return result;
}


// df/dy с результатами на плоскости
TableFunction df_dy_(const TableFunction& f, const Grid& g) {
    TableFunction result;
    result.points.resize(f.points.size());

    for (size_t i = 0; i < f.points.size(); i++) {
        for (size_t j = 0; j < f.points[i].size(); j++) {
            result.points[i][j] = df_dy(f, g, static_cast<int>(i), static_cast<int>(j));
        }
    }

    return result;
}


std::vector<TableFunction> nabla(const TableFunction& f, const Grid& g) {
    std::vector<TableFunction> result(2);

    result[0] = df_dx_(f, g);
    result[1] = df_dy_(f, g);

    return result;
}


// Дивергенция в точке
double divergence(const TableFunction& f, const Grid& g, int i, int j) {
    return df_dx(f, g, i, j) + df_dy(f, g, i, j);
}
