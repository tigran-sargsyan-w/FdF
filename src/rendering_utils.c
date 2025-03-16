/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:44:13 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/16 10:44:17 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	compute_projected_point(t_map *map, int i, int j, t_point2d offset)
{
	t_point	point;

	point = (t_point){j * map->scale, i * map->scale, map->values[i][j]};
	point = rotate_point(point, map);
	point.x *= map->zoom_factor;
	point.y *= map->zoom_factor;
	point.z *= map->zoom_factor;
	if (map->projection_mode == ISO)
		map->render_points[i][j] = to_isometric(point, map->flatten_factor);
	else if (map->projection_mode == PARALLEL)
		map->render_points[i][j] = to_parallel(point);
	else if (map->projection_mode == ORTHO)
		map->render_points[i][j] = to_orthographic(point);
	else
		map->render_points[i][j] = to_isometric(point, map->flatten_factor);
	map->render_points[i][j].x += offset.x + map->trans_x;
	map->render_points[i][j].y += offset.y + map->trans_y;
}

void	update_projected_points(t_vars *vars)
{
	t_point2d	offset;
	int			i;
	int			j;

	compute_bounding_box(vars);
	offset.x = ((vars->screen_width + MENU_WIDTH) - (vars->box.max_x
				- vars->box.min_x)) / 2 - vars->box.min_x;
	offset.y = (vars->screen_height - (vars->box.max_y - vars->box.min_y)) / 2
		- vars->box.min_y;
	i = 0;
	while (i < vars->map->rows)
	{
		j = 0;
		while (j < vars->map->columns)
		{
			compute_projected_point(vars->map, i, j, offset);
			j++;
		}
		i++;
	}
}
