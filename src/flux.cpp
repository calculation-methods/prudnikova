#include "flux.h"

// Функция для расчёта площади, прошедшей через правую грань ячейки
double calculateRightFlux(const polygon& p, const computation_params& cond, int i, int j) 
{
    polygon p1;
    p1.vertex_num = 0;

    for (int k = 0; k < p.vertex.size(); k++) {
        const double x = p.vertex[k].x + cond.velocity.points[i + 1][j] * cond.delta_t;
        const double y = p.vertex[k].y;
        // Проверяем, прошла ли точка через правую грань ячейки
        if (x > (i + 1) * cond.grid_f.delta_x) {
            p1.vertex.push_back({x, y});
            p1.vertex_num += 1;
        } else {
            p1.vertex.push_back({(i + 1) * cond.grid_f.delta_x, y});
            p1.vertex_num += 1;
        }
    }

    return PLIC::polygon_area(p1);
}

// Функция для расчёта площади, прошедшей через верхнюю грань ячейки
double calculateUpperFlux(const polygon& p, const computation_params& cond, int i, int j) 
{
    polygon p1;
    p1.vertex_num = 0;

    for (int k = 0; k < p.vertex.size(); k++) {
        const double x = p.vertex[k].x;
        const double y = p.vertex[k].y + cond.velocity.points[i][j + 1] * cond.delta_t;
        // Проверяем, прошла ли точка через верхнюю грань ячейки
        if (y > (j + 1) * cond.grid_f.delta_y) {
            p1.vertex.push_back({x, y});
            p1.vertex_num += 1;
        } else {
            p1.vertex.push_back({x, (j + 1) * cond.grid_f.delta_y});
            p1.vertex_num += 1;
        }
    }

    return PLIC::polygon_area(p1);
}

// Функция для расчёта площади, прошедшей через левую грань ячейки
double calculateLeftFlux(const polygon& p, const computation_params& cond, int i, int j) 
{
    if (i == 0) {
        return 0;
    }

    polygon p1;
    p1.vertex_num = 0;

    for (int k = 0; k < p.vertex.size(); k++) {
        const double x = p.vertex[k].x + cond.velocity.points[i - 1][j] * cond.delta_t;
        const double y = p.vertex[k].y;
        // Проверяем, прошла ли точка через левую грань ячейки
        if (x > i * cond.grid_f.delta_x) {
            p1.vertex.push_back({x, y});
            p1.vertex_num += 1;
        } else {
            p1.vertex.push_back({i * cond.grid_f.delta_x, y});
            p1.vertex_num += 1;
        }
    }

    return PLIC::polygon_area(p1);
}

// Функция для расчёта площади, прошедшей через нижнюю грань ячейки
double calculateLowerFlux(const polygon& p, const computation_params& cond, int i, int j) 
{
    if (j == 0) {
        return 0;
    }

    polygon p1;
    p1.vertex_num = 0;

    for (int k = 0; k < p.vertex.size(); k++) {
        const double x = p.vertex[k].x;
        const double y = p.vertex[k].y + cond.velocity.points[i][j - 1] * cond.delta_t;
        // Проверяем, прошла ли точка через нижнюю грань ячейки
        if (y > j * cond.grid_f.delta_y) {
            p1.vertex.push_back({x, y});
            p1.vertex_num += 1;
        } else {
            p1.vertex.push_back({x, j * cond.grid_f.delta_y});
            p1.vertex_num += 1;
        }
    }

    return PLIC::polygon_area(p1);
}

// Расчёт нового состояния ячейки с учётом двух потоков (вертикально)
double fCellStepUpDown(const polygon& p, const computation_params& cond, const table_function& f, int i, int j) 
{
    double newArea = f.points[i][j] + calculateLowerFlux(p, cond, i, j) - calculateUpperFlux(p, cond, i, j);

    if (newArea <= 1) {
        return newArea;
    } else if (newArea > 1) {
        return 1.0;
    }
    return 0;
}

// Расчёт нового состояния ячейки с учётом двух потоков (горизонтально)
double fCellStepLeftRight(const polygon& p, const computation_params& cond, const table_function& f, int i, int j) 
{
    double newArea = f.points[i][j] + calculateLeftFlux(p, cond, i, j) - calculateRightFlux(p, cond, i, j);

    if (newArea) {
        return newArea;
    } else if (newArea > 1) {
        return 1.0;
    }
    return 0;
}
