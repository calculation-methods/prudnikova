#include "structures.h"

table_function& table_function::operator=(const table_function& other) 
{
    if (this != &other) {
        points = other.points;
        f_grid = other.f_grid;
    }
    return *this;
}

table_function::table_function() : points(0) {}

table_function::table_function(int n, int m) : points(n, std::vector<double>(m, 0.0)), f_grid(n, m) {}

bool operator==(const table_function& lhs, const table_function& rhs)
{
    if (lhs.points.size() != rhs.points.size()) return false;
    for (size_t i = 0; i < lhs.points.size(); ++i)
    {
        if (lhs.points[i].size() != rhs.points[i].size()) return false;
        for (size_t j = 0; j < lhs.points[i].size(); ++j)
        {
            if (std::fabs(lhs.points[i][j] - rhs.points[i][j]) >= 1e-10) return false;
        }
    }
    return true;
}

computation_params::computation_params() : velocity(), delta_t(0.0), grid_f() {}

computation_params::computation_params(table_function vel, double dt, rectangular_grid g)
        : velocity(vel), delta_t(dt), grid_f(g) {}

bool operator==(const computation_params& lhs, const computation_params& rhs)
{
    return lhs.velocity == rhs.velocity
        && std::fabs(lhs.delta_t - rhs.delta_t) < 1e-10
        && lhs.grid_f == rhs.grid_f;
}

