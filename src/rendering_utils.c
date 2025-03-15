/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:44:13 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/15 17:51:42 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	compute_projected_point(t_map *map, int i, int j, t_point2d offset)
{
	t_point	pt;

	pt = (t_point){j * map->scale, i * map->scale, map->values[i][j]};
	pt = rotate_point(pt, map);
	pt.x *= map->zoom_factor;
	pt.y *= map->zoom_factor;
	pt.z *= map->zoom_factor;
	if (map->projection_mode == ISO)
		map->projected_points[i][j] = to_isometric(pt, map->flatten_factor);
	else if (map->projection_mode == PARALLEL)
		map->projected_points[i][j] = to_parallel(pt);
	else if (map->projection_mode == ORTHO)
		map->projected_points[i][j] = to_orthographic(pt);
	else
		map->projected_points[i][j] = to_isometric(pt, map->flatten_factor);
	map->projected_points[i][j].x += offset.x + map->trans_x;
	map->projected_points[i][j].y += offset.y + map->trans_y;
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
