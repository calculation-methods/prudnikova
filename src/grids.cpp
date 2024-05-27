#include "grids.h"

// Функция, вычисляющая координаты вершин ij-ой ячейки сетки g
polygon polygon_from_cell(const grid& g, const int i, const int j) 
{
    point lu, ld, ru, rd;

    // Левый нижний угол
    ld.x = g.delta_x * i;
    ld.y = g.delta_y * j;
    // Правый нижний угол
    rd.x = g.delta_x * i + 1;
    rd.y = g.delta_y * j; 
    // Правый верхний угол
    ru.x = g.delta_x * i + 1;
    ru.y = g.delta_y * j + 1; 
    // Левый верхний угол
    lu.x = g.delta_x * i;
    lu.y = g.delta_y * j + 1;

    polygon cell(4);
    cell.vertex[0] = lu;
    cell.vertex[1] = ld;
    cell.vertex[2] = rd;
    cell.vertex[3] = ru;

    return cell;
}

std::vector<line_segment> line_segment_from_cell(grid g, const int i, const int j) 
{
    polygon cell = polygon_from_cell(g, i, j);

    std::vector<line_segment> edges;

    for (int cur = 0; cur < cell.vertex.size(); cur++) 
    {
        int next = (cur + 1) % 4;

        line_segment line;

        line.n.x = std::abs(cell.vertex[next].x - cell.vertex[cur].x);
        line.n.y = std::abs(cell.vertex[next].y - cell.vertex[cur].y);

        if (line.n.x) 
        {
            line.n.x /= std::sqrt(line.n.x * line.n.x + line.n.y * line.n.y);
        }
        if (line.n.y) 
        {
            line.n.y /= std::sqrt(line.n.x * line.n.x + line.n.y * line.n.y);
        }
        // Вычисляем значение по формуле линейной функции: n_x * x + n_y * y - rho = 0
        line.rho = line.n.x * cell.vertex[cur].x + line.n.y * cell.vertex[cur].y;

        edges.push_back(line);
    }

    return edges;
}

bool is_point_in_cell(const point& vertex, const grid& g, const int i, const int j) 
{
    return (vertex.x >= g.delta_x * i && vertex.x <= g.delta_x * (i + 1) &&
            vertex.y >= g.delta_y * j && vertex.y <= g.delta_y * (j + 1));
}