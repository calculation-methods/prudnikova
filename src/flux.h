#ifndef FLUX_H
#define FLUX_H

#include "PLIC.h"
#include "approximation.h"

// Функция для расчёта площади, прошедшей через правую грань ячейки
double flux_right(const polygon& p, const computation_params& cond, int i, int j);

// Функция для расчёта площади, прошедшей через верхнюю грань ячейки
double flux_up(const polygon& p, const computation_params& cond, int i, int j);

// Функция для расчёта площади, прошедшей через левую грань ячейки
double flux_left(const polygon& p, const computation_params& cond, int i, int j);

// Функция для расчёта площади, прошедшей через нижнюю грань ячейки
double flux_down(const polygon& p, const computation_params& cond, int i, int j);

// Расчёт нового состояния ячейки с учётом четырёх потоков (вертикально)
double flow_increment_down_up(const computation_params& cond, const table_function& f, const int i, const int j, const grid& f_grid);

// Расчёт нового состояния ячейки с учётом четырёх потоков (горизонтально)
double flow_increment_left_right(const computation_params& cond, const table_function& f, const int i, const int j, const grid& f_grid);

#endif
