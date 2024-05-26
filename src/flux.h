#ifndef FLUX_H
#define FLUX_H

#include "PLIC.h"
#include "approximation.h"

// Функция для расчёта площади, прошедшей через правую грань ячейки
double calculateRightFlux(const polygon& p, const computation_params& cond, int i, int j);

// Функция для расчёта площади, прошедшей через верхнюю грань ячейки
double calculateUpperFlux(const polygon& p, const computation_params& cond, int i, int j);

// Функция для расчёта площади, прошедшей через левую грань ячейки
double calculateLeftFlux(const polygon& p, const computation_params& cond, int i, int j);

// Функция для расчёта площади, прошедшей через нижнюю грань ячейки
double calculateLowerFlux(const polygon& p, const computation_params& cond, int i, int j);

// Расчёт нового состояния ячейки с учётом четырёх потоков (вертикально)
double fCellStepUpDown(const polygon& p, const computation_params& cond, const table_function& f, int i, int j);

// Расчёт нового состояния ячейки с учётом четырёх потоков (горизонтально)
double fCellStepLeftRight(const polygon& p, const computation_params& cond, const table_function& f, int i, int j);

#endif
