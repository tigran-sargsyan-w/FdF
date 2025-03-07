/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbox_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:51:40 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/07 12:15:37 by tsargsya         ###   ########.fr       */
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
void	compute_bounding_box(t_map *map, t_bbox *box)
{
	int			i;
	int			j;
	t_point		current;
	t_point2d	proj;

	i = 0;
	init_bbox(box);
	while (i < map->rows)
	{
		j = 0;
		while (j < map->columns)
		{
			current = (t_point){j * map->scale, i * map->scale,
				map->values[i][j]};
			proj = iso_projection(current);
			update_bbox(box, proj);
			j++;
		}
		i++;
	}
}
