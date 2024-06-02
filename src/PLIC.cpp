#include "PLIC.h"

#include "line_equation.h"

std::optional<point> PLIC::line_line_intersection(const line_equation &line_eq1, const line_equation &line_eq2)
{
  return line_eq1.cross(line_eq2);
}

std::optional<point> PLIC::line_line_intersection(const line_segment &f1, const line_segment &f2)
{
    const double normal_1_x = f1.n.x;
    const double normal_1_y = f1.n.y;
    const double distance_1 = f1.rho;

    const double normal_2_x = f2.n.x;
    const double normal_2_y = f2.n.y;
    const double distance_2 = f2.rho;

    const double det = normal_1_x * normal_2_y - normal_1_y * normal_2_x;

    // If det equaol to 0 => lines are parallel or the same
    if (std::fabs(det) < PLIC::epsilon) {
        return std::nullopt;
    }

    point ans;

    ans.x = (normal_2_y * distance_1 - normal_1_y * distance_2) / det;
    ans.y = (normal_1_x * distance_2 - normal_2_x * distance_1) / det;

    return ans;
}

bool PLIC::point_to_line_relation(const point &pnt, const line_equation &line_eq)
{
  return line_eq.sustitute(pnt) >= 0.;
}

bool PLIC::point_to_line_relation(const point& point, const line_segment& lf)
{
    const double normal_x = lf.n.x;
    const double normal_y = lf.n.y;
    const double vertex_x = point.x;
    const double vertex_y = point.y;

    return normal_x * vertex_x + normal_y * vertex_y - lf.rho >= 0;
}

polygon PLIC::collect_polygon_vertices(const line_equation &line_eq, const grid &grid, const int i, const int j)
{
    // x = const
    const line_equation left_edge (1., 0., -(grid.delta_y * i));
    const line_equation right_edge (1., 0., -(grid.delta_y * (i - 1)));

    // y = const
    const line_equation up_edge (0., 1., -(grid.delta_y * j));
    const line_equation down_edge (0., 1., -(grid.delta_y * (j - 1)));

    const std::optional<point> left_point = line_eq.cross (left_edge);
    const std::optional<point> right_point = line_eq.cross (right_edge);
    const std::optional<point> up_point = line_eq.cross (up_edge);
    const std::optional<point> down_point = line_eq.cross (down_edge);

    std::vector<point> intersection;
    if (!left_point)
    {
      intersection.push_back(up_point.value ());
      intersection.push_back(down_point.value ());
    }
    else if (!up_point)
    {
      intersection.push_back(left_point.value ());
      intersection.push_back(right_point.value ());
    }
    else
    {
      std::vector<point> intersection_points = {up_point.value (), down_point.value (), left_point.value (), right_point.value ()};
      std::ranges::sort (intersection_points, [] (const point &left, const point &right) { return left.x < right.x; });
      intersection.push_back(intersection_points[1]);
      intersection.push_back(intersection_points[2]);
    }

    polygon cell = get_ij_cell_coords(grid, i, j);
    for (const point &vertex : cell.vertex)
      if (point_to_line_relation(vertex, line_eq);
        result.vertex.push_back(vertex);

    polygon result;

    point cell_centroid;
    cell_centroid.x = grid.delta_x * (i + 0.5);
    cell_centroid.y = grid.delta_y * (j + 0.5);

    std::sort(result.vertex.begin(), result.vertex.end(), [&](const point& p1, const point& p2) {
        double angle1 = atan2(p1.y - cell_centroid.y, p1.x - cell_centroid.x);
        double angle2 = atan2(p2.y - cell_centroid.y, p2.x - cell_centroid.x);
        return angle1 < angle2;
    });

    return result;
}

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
        result.vertex_num += intersection.size();
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
        result.vertex_num += intersection.size();
    } else
    {
        std::vector<line_segment> edges = line_segment_from_cell(grid, i, j);

        for (int k = 0; k < edges.size(); k++) {
            std::optional<point> is_crossing = PLIC::line_line_intersection(lf, edges[k]);
            point cross = *is_crossing;

            if (is_crossing.has_value())
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
            std::vector<point>::iterator find_vertex = find(result.vertex.begin(), result.vertex.end(), intersection[k]);
            if (point_to_line_relation(intersection[k], lf) && find_vertex == result.vertex.end())
            {
                result.vertex.push_back(intersection[k]);
                result.vertex_num += 1;
            }
        }
    }

    polygon cell = get_ij_cell_coords(grid, i, j);

    for (int k = 0; k < cell.vertex.size(); k++)
    {
        std::vector<point>::iterator find_vertex = find(result.vertex.begin(), result.vertex.end(), cell.vertex[k]);
        if (point_to_line_relation(cell.vertex[k], lf) && find_vertex == result.vertex.end())
        {
            result.vertex.push_back(cell.vertex[k]);
            result.vertex_num += 1;
        }
    }

    point cell_centroid;
    cell_centroid.x = grid.delta_x * (i + 0.5);
    cell_centroid.y = grid.delta_y * (j + 0.5);

    std::sort(result.vertex.begin(), result.vertex.end(), [&](const point& p1, const point& p2) {
        double angle1 = atan2(p1.y - cell_centroid.y, p1.x - cell_centroid.x);
        double angle2 = atan2(p2.y - cell_centroid.y, p2.x - cell_centroid.x);
        return angle1 < angle2;
    });

    return result;
}

double PLIC::polygon_area(const polygon &plgn)
{
  return plgn.area();
}
