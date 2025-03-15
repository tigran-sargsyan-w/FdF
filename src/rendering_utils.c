/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:44:13 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/15 16:56:57 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_projected_points(t_vars *vars)
{
	t_point	rotated;
	int		x_offset;
	int		y_offset;
	int		i;
	int		j;

	compute_bounding_box(vars);
	x_offset = ((vars->screen_width + MENU_WIDTH) - (vars->box.max_x
				- vars->box.min_x)) / 2 - vars->box.min_x;
	y_offset = (vars->screen_height - (vars->box.max_y - vars->box.min_y)) / 2
		- vars->box.min_y;
	i = 0;
	while (i < vars->map->rows)
	{
		j = 0;
		while (j < vars->map->columns)
		{
			rotated = (t_point){j * vars->map->scale, i * vars->map->scale,
				vars->map->values[i][j]};
			rotated = rotate_point(rotated, vars->map);
			rotated.x *= vars->map->zoom_factor;
			rotated.y *= vars->map->zoom_factor;
			rotated.z *= vars->map->zoom_factor;
			if (vars->map->projection_mode == ISO)
				vars->map->projected_points[i][j] = iso_projection(rotated,
						vars->map->flatten_factor);
			else if (vars->map->projection_mode == PARALLEL)
				vars->map->projected_points[i][j] = parallel_projection(rotated,
						vars->map->parallel_factor);
			else if (vars->map->projection_mode == ORTHO)
				vars->map->projected_points[i][j] = ortho_projection(rotated);
			else
				vars->map->projected_points[i][j] = iso_projection(rotated,
						vars->map->flatten_factor);
			vars->map->projected_points[i][j].x += x_offset
				+ vars->map->trans_x;
			vars->map->projected_points[i][j].y += y_offset
				+ vars->map->trans_y;
			j++;
		}
		i++;
	}
}
