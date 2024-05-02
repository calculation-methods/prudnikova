#include "structures.h"

// df/dx в точке
double df_dx(const NonlinearFunction& f, const Grid& g, int i) {
    if (i == 0) {
        // !! Возможно, придётся изменить, если будем рассматривать зеркальный вариант
        // Для первой и последней точек используем односторонние разности
        return (f.points[i + 1].y - f.points[i].y) / g.delta_x;
    } else if (i == static_cast<int>(f.points.size()) - 1) {
        (f.points[i].y - f.points[i - 1].y) / g.delta_x;
    } else {
        // Для остальных точек используем центральную разность
        // double left = (f.points[i].y - f.points[i - 1].y) / (g.delta_x);
        // double right = (f.points[i + 1].y - f.points[i].y) / (g.delta_x);
        // return (left + right) / 2.0;
        return (f.points[i + 1].y - f.points[i - 1].y) / (2.0 * g.delta_x);
    }
}


// df/dy в точке
double df_dy(const NonlinearFunction& f, const Grid& g, int i) {
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
NonlinearFunction df_dx_(const NonlinearFunction& f, const Grid& g) {
    NonlinearFunction result;
    result.points.resize(f.points.size());

    for (size_t i = 0; i < f.points.size(); i++) {
        result.points[i].x = f.points[i].x;
        result.points[i].y = df_dx(f, g, static_cast<int>(i));
    }

    return result;
}


// df/dy с результатами на плоскости
NonlinearFunction df_dy_(const NonlinearFunction& f, const Grid& g) {
    NonlinearFunction result;
    result.points.resize(f.points.size());

    for (size_t i = 0; i < f.points.size(); i++) {
        result.points[i].x = f.points[i].x;
        result.points[i].y = df_dy(f, g, static_cast<int>(i));
    }

    return result;
}


std::vector<NonlinearFunction> nabla(const NonlinearFunction& f, const Grid& g) {
    std::vector<NonlinearFunction> result(2);

    result[0] = df_dx_(f, g);
    result[1] = df_dy_(f, g);

    return result;
}


// Дивергенция на плоскости
NonlinearFunction divergence(const NonlinearFunction& f, const Grid& g) {
    NonlinearFunction result;
    result.points.resize(f.points.size());

    for (size_t i = 0; i < f.points.size(); i++) {
        result.points[i].x = f.points[i].x;
        result.points[i].y = df_dx(f, g, static_cast<int>(i)) + df_dy(f, g, static_cast<int>(i));
    }

    return result;
}

// Дивергенция в точке
double divergence(const NonlinearFunction& f, const Grid& g, int i) {
    return df_dx(f, g, i) + df_dy(f, g, i);
}
