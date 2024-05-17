#ifndef FLUX_H
#define FLUX_H

#include "PLIC.h"
#include "approximation.h"

// Функция для расчёта площади, прошедшей через правую грань ячейки
double calculateRightFlux(const Polygon& p, const ComputationParams& cond, int i, int j);

// Функция для расчёта площади, прошедшей через верхнюю грань ячейки
double calculateUpperFlux(const Polygon& p, const ComputationParams& cond, int i, int j);

// Функция для расчёта площади, прошедшей через левую грань ячейки
double calculateLeftFlux(const Polygon& p, const ComputationParams& cond, int i, int j);

// Функция для расчёта площади, прошедшей через нижнюю грань ячейки
double calculateLowerFlux(const Polygon& p, const ComputationParams& cond, int i, int j);

// Расчёт нового состояния ячейки с учётом четырёх потоков (вертикально)
double fCellStepUpDown(const Polygon& p, const ComputationParams& cond, const TableFunction& f, int i, int j);

// Расчёт нового состояния ячейки с учётом четырёх потоков (горизонтально)
double fCellStepLeftRight(const Polygon& p, const ComputationParams& cond, const TableFunction& f, int i, int j);

#endif
