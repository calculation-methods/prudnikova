#ifndef FLUX_H
#define FLUX_H

#include "PLIC.h"

// Функция для расчёта площади, прошедшей через правую грань ячейки
double calculateRightFlux(const Polygon& p, const TableFunction& u, double t, Grid g, int i, int j);

// Функция для расчёта площади, прошедшей через верхнюю грань ячейки
double calculateUpperFlux(const Polygon& p, const TableFunction& v, double t, Grid g, int i, int j);

#endif
