#ifndef ASSEMBLE_H
#define ASSEMBLE_H

#include "flux.h"
#include "rungekutta.h"

// Расчёт новой функции f_(n+1)
table_function f_full_step(const computation_params& vertical, const computation_params& horizontal, const table_function& f);

// Вычисляет конечный вид функции f
table_function apply_method(const table_function& f, const computation_params& vertical, const computation_params& horizontal, double time);

#endif