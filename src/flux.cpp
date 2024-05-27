#include "flux.h"

// Функция для расчёта площади, прошедшей через правую грань ячейки
double flux_right(const polygon& p, const computation_params& cond, int i, int j) 
{
    polygon p1;
    p1.vertex_num = 0;

    double cell_edge_x = (i + 1) * cond.grid_f.delta_x;
    point edge_down = {(i + 1) * cond.grid_f.delta_x, j * cond.grid_f.delta_y};
    point edge_up = {(i + 1) * cond.grid_f.delta_x, (j + 1) * cond.grid_f.delta_y};

    line_segment cell_edge = create_edge(edge_down, edge_up);

    for (int k = 0; k < p.vertex.size(); k++) {
        double x = p.vertex[k].x + cond.delta_t * cond.velocity.points[i + 1][j];
        double y = p.vertex[k].y;
        // Проверяем, прошла ли точка через правую грань ячейки
        if (x > cell_edge_x) 
        {
            p1.vertex.push_back({x, y});
            p1.vertex_num += 1;
        } else 
        {
            int size = p.vertex.size();
            int next_vert_ind = (k + 1) % size;
            int prev_vert_ind = k - 1;
            line_segment poly_edge = create_edge(p.vertex[k], p.vertex[next_vert_ind]);

            point cross;

            if (PLIC::line_line_intersection(poly_edge, cell_edge, cross)) 
            {
                if (is_point_in_cell(cross, cond.grid_f, i, j)) 
                {
                    p1.vertex.push_back(cross);
                    p1.vertex_num += 1;
                }
            } else
            {
                if (k == 0) 
                {
                    int prev_vert_ind = size - 1;
                } else 
                {
                poly_edge = create_edge(p.vertex[k], p.vertex[prev_vert_ind]);
                if (PLIC::line_line_intersection(poly_edge, cell_edge, cross)) 
                {
                    if (is_point_in_cell(cross, cond.grid_f, i, j)) 
                    {
                        p1.vertex.push_back(cross);
                        p1.vertex_num += 1;
                    }
                }
            }
        }
    }
    }

    return PLIC::polygon_area(p1);
}

// Функция для расчёта площади, прошедшей через верхнюю грань ячейки
double flux_up(const polygon& p, const computation_params& cond, int i, int j) 
{
    polygon p1;
    p1.vertex_num = 0;

    double cell_edge_y = (j + 1) * cond.grid_f.delta_y;
    point edge_left = {(i) * cond.grid_f.delta_x, (j + 1) * cond.grid_f.delta_y};
    point edge_right = {(i + 1) * cond.grid_f.delta_x, (j + 1) * cond.grid_f.delta_y};

    line_segment cell_edge = create_edge(edge_left, edge_right);

    for (int k = 0; k < p.vertex.size(); k++) {
        const double x = p.vertex[k].x;
        const double y = p.vertex[k].y + cond.velocity.points[i][j + 1] * cond.delta_t;
        // Проверяем, прошла ли точка через верхнюю грань ячейки
        if (y > cell_edge_y) {
            p1.vertex.push_back({x, y});
            p1.vertex_num += 1;
        } else 
        {
            int size = p.vertex.size();
            int next_vert_ind = (k + 1) % size;
            int prev_vert_ind = k - 1;
            line_segment poly_edge = create_edge(p.vertex[k], p.vertex[next_vert_ind]);

            point cross;

            if (PLIC::line_line_intersection(poly_edge, cell_edge, cross)) 
            {
                if (is_point_in_cell(cross, cond.grid_f, i, j)) 
                {
                    p1.vertex.push_back(cross);
                    p1.vertex_num += 1;
                }
            } else
            {
                if (k == 0) 
                {
                    int prev_vert_ind = size - 1;
                } else 
                {
                poly_edge = create_edge(p.vertex[k], p.vertex[prev_vert_ind]);
                if (PLIC::line_line_intersection(poly_edge, cell_edge, cross)) 
                {
                    if (is_point_in_cell(cross, cond.grid_f, i, j)) 
                    {
                        p1.vertex.push_back(cross);
                        p1.vertex_num += 1;
                    }
                }
            }
        }
    }
    }

    return PLIC::polygon_area(p1);
}

// Функция для расчёта площади, прошедшей через левую грань ячейки
double flux_left(const polygon& p, const computation_params& cond, int i, int j) 
{
    if (i == 0) {
        return 0;
    }

    polygon p1;
    p1.vertex_num = 0;

    double cell_edge_x = (i) * cond.grid_f.delta_x;
    point edge_down = {(i) * cond.grid_f.delta_x, j * cond.grid_f.delta_y};
    point edge_up = {(i) * cond.grid_f.delta_x, (j + 1) * cond.grid_f.delta_y};

    line_segment cell_edge = create_edge(edge_down, edge_up);

    for (int k = 0; k < p.vertex.size(); k++) {
        const double x = p.vertex[k].x + cond.velocity.points[i - 1][j] * cond.delta_t;
        const double y = p.vertex[k].y;
        // Проверяем, прошла ли точка через левую грань ячейки
        if (x > cell_edge_x) {
            p1.vertex.push_back({x, y});
            p1.vertex_num += 1;
        } else 
        {
            int size = p.vertex.size();
            int next_vert_ind = (k + 1) % size;
            int prev_vert_ind = k - 1;
            line_segment poly_edge = create_edge(p.vertex[k], p.vertex[next_vert_ind]);

            point cross;

            if (PLIC::line_line_intersection(poly_edge, cell_edge, cross)) 
            {
                if (is_point_in_cell(cross, cond.grid_f, i, j)) 
                {
                    p1.vertex.push_back(cross);
                    p1.vertex_num += 1;
                }
            } else
            {
                if (k == 0) 
                {
                    int prev_vert_ind = size - 1;
                } else 
                {
                poly_edge = create_edge(p.vertex[k], p.vertex[prev_vert_ind]);
                if (PLIC::line_line_intersection(poly_edge, cell_edge, cross)) 
                {
                    if (is_point_in_cell(cross, cond.grid_f, i, j)) 
                    {
                        p1.vertex.push_back(cross);
                        p1.vertex_num += 1;
                    }
                }
            }
        }
    }
    }

    return PLIC::polygon_area(p1);
}

// Функция для расчёта площади, прошедшей через нижнюю грань ячейки
double flux_down(const polygon& p, const computation_params& cond, int i, int j) 
{
    if (j == 0) {
        return 0;
    }

    polygon p1;
    p1.vertex_num = 0;

    double cell_edge_y = (j) * cond.grid_f.delta_y;
    point edge_left = {(i) * cond.grid_f.delta_x, (j) * cond.grid_f.delta_y};
    point edge_right = {(i + 1) * cond.grid_f.delta_x, (j) * cond.grid_f.delta_y};

    line_segment cell_edge = create_edge(edge_left, edge_right);

    for (int k = 0; k < p.vertex.size(); k++) {
        const double x = p.vertex[k].x;
        const double y = p.vertex[k].y + cond.velocity.points[i][j - 1] * cond.delta_t;
        // Проверяем, прошла ли точка через нижнюю грань ячейки
        if (y > cell_edge_y) {
            p1.vertex.push_back({x, y});
            p1.vertex_num += 1;
        } else 
        {
            int size = p.vertex.size();
            int next_vert_ind = (k + 1) % size;
            int prev_vert_ind = k - 1;
            line_segment poly_edge = create_edge(p.vertex[k], p.vertex[next_vert_ind]);

            point cross;

            if (PLIC::line_line_intersection(poly_edge, cell_edge, cross)) 
            {
                if (is_point_in_cell(cross, cond.grid_f, i, j)) 
                {
                    p1.vertex.push_back(cross);
                    p1.vertex_num += 1;
                }
            } else
            {
                if (k == 0) 
                {
                    int prev_vert_ind = size - 1;
                } else 
                {
                poly_edge = create_edge(p.vertex[k], p.vertex[prev_vert_ind]);
                if (PLIC::line_line_intersection(poly_edge, cell_edge, cross)) 
                {
                    if (is_point_in_cell(cross, cond.grid_f, i, j)) 
                    {
                        p1.vertex.push_back(cross);
                        p1.vertex_num += 1;
                    }
                }
            }
        }
    }
    }

    return PLIC::polygon_area(p1);
}

// Расчёт нового состояния ячейки с учётом двух потоков (вертикально)
double flow_increment_down_up(const computation_params& cond, const table_function& f, const int i, const int j, const grid& f_grid) 
{
    line_segment approx_cur = build_linear_approximation(f, f_grid, i, j);
    polygon curr_cell_poly = PLIC::collect_polygon_vertices(approx_cur, f_grid, i, j);

    double newArea = 0;

    if (j == 0) 
    {
        newArea -= flux_up(curr_cell_poly, cond, i, j);
        return newArea;
    }

    line_segment approx_prev = build_linear_approximation(f, f_grid, i, j - 1);
    polygon prev_cell_poly = PLIC::collect_polygon_vertices(approx_prev, f_grid, i, j - 1);
    
    newArea = flux_down(prev_cell_poly, cond, i, j) - flux_up(curr_cell_poly, cond, i, j);

    if (newArea) {
        return newArea;
    } 
    return 0;
}

// Расчёт нового состояния ячейки с учётом двух потоков (горизонтально)
double flow_increment_left_right(const computation_params& cond, const table_function& f, const int i, const int j, const grid& f_grid) 
{
    line_segment approx_cur = build_linear_approximation(f, f_grid, i, j);
    polygon curr_cell_poly = PLIC::collect_polygon_vertices(approx_cur, f_grid, i, j);

    double newArea = 0;

    if (i == 0) 
    {
        newArea -= flux_right(curr_cell_poly, cond, i, j);
        return newArea;
    }

    line_segment approx_prev = build_linear_approximation(f, f_grid, i - 1, j);
    polygon prev_cell_poly = PLIC::collect_polygon_vertices(approx_prev, f_grid, i - 1, j);
    
    newArea = flux_left(prev_cell_poly, cond, i, j) - flux_right(curr_cell_poly, cond, i, j);
    if (newArea) {
        return newArea;
    }
    return 0;
}
