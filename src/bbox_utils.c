/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbox_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:51:40 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/16 11:47:50 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to create border box for the map
static void	init_bbox(t_bbox *box)
{
	box->min_x = INT_MAX;
	box->max_x = INT_MIN;
	box->min_y = INT_MAX;
	box->max_y = INT_MIN;
}

// Function to update bounding box with a new point
static void	update_bbox(t_bbox *box, t_point2d proj)
{
	if (proj.x < box->min_x)
		box->min_x = proj.x;
	if (proj.x > box->max_x)
		box->max_x = proj.x;
	if (proj.y < box->min_y)
		box->min_y = proj.y;
	if (proj.y > box->max_y)
		box->max_y = proj.y;
}

// Function to compute the center of the grid
t_point	get_center(t_map *map)
{
	t_point	center;

	center.x = (map->columns - 1) * map->scale / 2;
	center.y = (map->rows - 1) * map->scale / 2;
	center.z = 0;
	return (center);
}

// Function to compute bounding box for the map
void	compute_bounding_box(t_vars *vars)
{
	int			i;
	int			j;
	t_point		current;
	t_point2d	proj;

	i = 0;
	init_bbox(&vars->box);
	while (i < vars->map->rows)
	{
		j = 0;
		while (j < vars->map->columns)
		{
			current = (t_point){j * vars->map->scale, i * vars->map->scale,
				vars->map->values[i][j]};
			if (vars->map->projection_mode == PARALLEL)
				proj = to_parallel(current);
			else if (vars->map->projection_mode == ORTHO)
				proj = to_orthographic(current);
			else
				proj = to_isometric(current, vars->map->flatten_factor);
			update_bbox(&vars->box, proj);
			j++;
		}
		i++;
	}
}
