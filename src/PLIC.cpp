#include "PLIC.h"

// Функция 1
bool PLIC::line_line_intersection(line_segment f1, line_segment f2, point& ans) 
{
    const double n1_x = f1.n.x;
    const double n1_y = f1.n.y;
    const double rho1 = f1.rho;

    const double n2_x = f2.n.x;
    const double n2_y = f2.n.y;
    const double rho2 = f2.rho;

    // Вычисляем определитель
    const double det = n1_x * n2_y - n1_y * n2_x;

    // Если определитель равен 0, линии параллельны или совпадают
    if (std::fabs(det) < 1e-10) {
        return false;
    }

    ans.x = (n2_y * rho1 - n1_y * rho2) / det;
    ans.y = (n1_x * rho2 - n2_x * rho1) / det;

    return true;
}

// Функция 2
bool PLIC::is_point_in_phase1(const point& point, const line_segment& lf) 
{
    const double n_x = lf.n.x;
    const double n_y = lf.n.y;
    const double x_v = point.x;
    const double y_v = point.y;

    return (n_x * x_v + n_y * y_v - lf.rho >= 0);
}


// Функция 3: Сбор вершин многоугольника
polygon PLIC::collect_polygon_vertices(const line_segment& lf, const grid& grid, const int i, const int j) 
{
    if (grid.x_size == 0 || grid.y_size == 0) 
    {
        return {};
    }
    polygon result;

    std::vector<point> intersection;

    bool is_line_cells_side_vertical = lf.n.x == 0 && (compute_y(lf, grid.delta_x * i) == grid.delta_y * j || compute_y(lf, grid.delta_x * i) == grid.delta_y * (j + 1));
    bool is_line_cells_side_horizontal = lf.n.y == 0 && (compute_x(lf, grid.delta_y * j) == grid.delta_x * i || compute_x(lf, grid.delta_y * j) == grid.delta_x * (i + 1));

    if (is_line_cells_side_vertical) 
    {
        point left, right;

        left.x = grid.delta_x * i;
        left.y = compute_y(lf, grid.delta_x * i);

        right.x = grid.delta_x * (i + 1);
        right.y = compute_y(lf, grid.delta_x * (i + 1));

        intersection.push_back(left);
        intersection.push_back(right);

        result.vertex = intersection;
    } else if (is_line_cells_side_horizontal) 
    {
        point down, up;

        down.y = grid.delta_y * j;
        down.x = compute_x(lf, grid.delta_y * j);

        up.y = grid.delta_y * (j + 1);
        up.x = compute_x(lf, grid.delta_y * (j + 1));

        intersection.push_back(down);
        intersection.push_back(up);

        result.vertex = intersection;
    } else 
    {
        std::vector<line_segment> edges = line_segment_from_cell(grid, i, j);

        for (int k = 0; k < edges.size(); k++) {
            point cross;

            if (PLIC::line_line_intersection(lf, edges[k], cross)) 
            {
                bool out_of_cell_bounds = cross.x > (i + 1) * grid.delta_x || cross.x < i * grid.delta_x || 
                cross.y > (j + 1) * grid.delta_y || cross.y < j * grid.delta_y;

                if (!out_of_cell_bounds) 
                {
                    intersection.push_back(cross);
                }
            }
        }

        for (int k = 0; k < intersection.size(); k++) 
        {
            result.vertex.push_back(intersection[k]);
            result.vertex_num += 1;
        }
    }

    polygon cell = polygon_from_cell(grid, i, j);

    // !! Так ли здесь применяется функция 2?
    for (int k = 0; k < cell.vertex.size(); k++)
    {
        std::vector<point>::iterator find_vertex = find(result.vertex.begin(), result.vertex.end(), cell.vertex[k]);
        if (is_point_in_phase1(cell.vertex[k], lf) && find_vertex == result.vertex.end())
        {
            result.vertex.push_back(cell.vertex[k]);
            result.vertex_num += 1;
        }
    }
    
    return result;
}


// Функция 4: расчёт площади многоугольника
double PLIC::polygon_area(const polygon& p) 
{
    double area = 0.0;
    const int size = p.vertex.size();

    // Вычисление площади с помощью формулы Гаусса
    for (int i = 0; i < size; i++) 
    {
        int j = (i + 1) % size;
        area += p.vertex[i].x * p.vertex[j].y - p.vertex[j].x * p.vertex[i].y;
    }

    area = std::abs(area) / 2.0;

    return area;
}