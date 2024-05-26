#include "rungekutta.h"


// Функция для решения уравнения переноса методом Рунге-Kутты 2-го порядка
table_function runge_kutta(const table_function& f, const table_function& u, const table_function& v, double dt, grid g) 
{
    size_t nx, ny;
    nx = g.x_size;
    ny = g.y_size;

    table_function f_tmp(nx, ny);
    table_function result(nx, ny);

    std::vector<table_function> grad = nabla(f, g);

    table_function grad_x = grad[0];
    table_function grad_y = grad[1];

    //  Метод Рунге-Kутты 2-го порядка
    for (int i = 0; i < nx; i++) 
    {
        for (int j = 0; j < ny; j++) 
        {
            double alpha_1 = f.points[i][j];
            double alpha_2;

            // Вычисление промежуточного значения функции заполнения
            alpha_2 = alpha_1 - dt * (u.points[i][j] * grad_x.points[i][j] + v.points[i][j] * grad_y.points[i][j]);
            f_tmp.points[i][j] = alpha_1 + 0.5 * dt * (u.points[i][j] * grad_x.points[i][j] + v.points[i][j] * grad_y.points[i][j]);

            // Обновление значения функции заполнения
            result.points[i][j] = alpha_1 + dt * (u.points[i][j] * grad_x.points[i][j] + v.points[i][j] * grad_y.points[i][j]);
        }
    }
    return result;
}
