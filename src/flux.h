#ifndef FLUX_H
#define FLUX_H

#include "PLIC.h"

// Функция для расчёта площади, прошедшей через правую грань ячейки
double calculateRightFlux(const Polygon& p, const Conditions& cond, int i, int j);

// Функция для расчёта площади, прошедшей через верхнюю грань ячейки
double calculateUpperFlux(const Polygon& p, const Conditions& cond, int i, int j);

// Функция для расчёта площади, прошедшей через левую грань ячейки
double calculateLeftFlux(const Polygon& p, const Conditions& cond, int i, int j);

// Функция для расчёта площади, прошедшей через нижнюю грань ячейки
double calculateLowerFlux(const Polygon& p, const Conditions& cond, int i, int j);

#endif
