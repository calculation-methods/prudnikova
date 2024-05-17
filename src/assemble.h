#ifndef ASSEMBLE_H
#define ASSEMBLE_H

#include "flux.h"

// Расчёт новой функции f_(n+1)
TableFunction fFullStep(const ComputationParams& vertical, const ComputationParams& horizontal, const TableFunction& f);

// Вычисляет конечный вид функции f
TableFunction applyMethod(const TableFunction& f, const ComputationParams& vertical, const ComputationParams& horizontal, double time);

#endif