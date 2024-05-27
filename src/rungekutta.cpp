#include "rungekutta.h"


// Функция для решения уравнения переноса методом Рунге-Kутты 2-го порядка
table_function runge_kutta(const table_function& f, const table_function& u, const table_function& v, double dt, grid f_grid) {
    // Создаем новую функцию таблицы для хранения следующего шага
    table_function next_step(f.points.size(), f.points[0].size());

    // Перебираем каждую ячейку сетки
    for (size_t i = 0; i < f_grid.x_size; ++i) {
        for (size_t j = 0; j < f_grid.y_size; ++j) {
            // Проверяем, находится ли ячейка на границе сетки
            bool is_edge_x = (i == 0 || i == f_grid.x_size - 1);
            bool is_edge_y = (j == 0 || j == f_grid.y_size - 1);

            // Расчет адвекции с учетом граничных условий
            double advection_x = 0.0;
            double advection_y = 0.0;

            if (!is_edge_x) {
                advection_x = u.points[i][j] * dt / f_grid.delta_x * (f.points[i][j] - f.points[i-1][j]);
            }

            if (!is_edge_y) {
                advection_y = v.points[i][j] * dt / f_grid.delta_y * (f.points[i][j] - f.points[i][j-1]);
            }

            // Обновляем значение функции распределения
            next_step.points[i][j] = f.points[i][j] - advection_x - advection_y;
        }
    }

    return next_step;
}