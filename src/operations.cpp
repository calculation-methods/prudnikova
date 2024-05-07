#include "operations.h"

// df/dx в точке
double df_dx(const TableFunction& f, const Grid& g, int i) {
    if (i == 0) {
        // !! Возможно, придётся изменить, если будем рассматривать зеркальный вариант
        // Для первой и последней точек используем односторонние разности
        return (f.points[i + 1].y - f.points[i].y) / g.delta_x;
    } else if (i == static_cast<int>(f.points.size()) - 1) {
        return (f.points[i].y - f.points[i - 1].y) / g.delta_x;
    }    
    // Для остальных точек используем центральную разность
    return (f.points[i + 1].y - f.points[i - 1].y) / (2.0 * g.delta_x);
}


// df/dy в точке
double df_dy(const TableFunction& f, const Grid& g, int i) {
    if (i == 0) {
        // !! Возможно, придётся изменить, если будем рассматривать зеркальный вариант
        // Для первой и последней точек используем односторонние разности
        return (f.points[i + 1].y - f.points[i].y) / g.delta_y;
    } else if (i == static_cast<int>(f.points.size()) - 1) {
        return (f.points[i].y - f.points[i - 1].y) / g.delta_y;
    } else {
        // Для остальных точек используем центральную разность
        return (f.points[i + 1].y - f.points[i - 1].y) / (2 * g.delta_y);
    }
}


// df/dx с результатами на плоскости
TableFunction df_dx_(const TableFunction& f, const Grid& g) {
    TableFunction result;
    result.points.resize(f.points.size());

    for (size_t i = 0; i < f.points.size(); i++) {
        result.points[i].x = f.points[i].x;
        result.points[i].y = df_dx(f, g, static_cast<int>(i));
    }

    return result;
}


// df/dy с результатами на плоскости
TableFunction df_dy_(const TableFunction& f, const Grid& g) {
    TableFunction result;
    result.points.resize(f.points.size());

    for (size_t i = 0; i < f.points.size(); i++) {
        result.points[i].x = f.points[i].x;
        result.points[i].y = df_dy(f, g, static_cast<int>(i));
    }

    return result;
}


std::vector<TableFunction> nabla(const TableFunction& f, const Grid& g) {
    std::vector<TableFunction> result(2);

    result[0] = df_dx_(f, g);
    result[1] = df_dy_(f, g);

    return result;
}


// Функция из суммы производных
TableFunction derivSumBuildF(const TableFunction& f, const Grid& g) {
    TableFunction result;
    result.points.resize(f.points.size());

    for (size_t i = 0; i < f.points.size(); i++) {
        result.points[i].x = f.points[i].x;
        result.points[i].y = df_dx(f, g, static_cast<int>(i)) + df_dy(f, g, static_cast<int>(i));
    }

    return result;
}

// Дивергенция в точке
double divergence(const TableFunction& f, const Grid& g, int i) {
    return df_dx(f, g, i) + df_dy(f, g, i);
}
