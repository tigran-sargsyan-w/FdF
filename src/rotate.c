/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:00:30 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/06 19:16:13 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to compute the center of the grid
static t_point	get_center(t_map *map)
{
	t_point	center;

	center.x = (map->columns - 1) * map->scale / 2;
	center.y = (map->rows - 1) * map->scale / 2;
	center.z = 0;
	return (center);
}

// Function to rotate a point around the X axis
static t_point	rotate_x(t_point p, float angle)
{
	t_point	rotated;
	float	temp_y;
	float	temp_z;

	rotated = p;
	temp_y = p.y * cos(angle) - p.z * sin(angle);
	temp_z = p.y * sin(angle) + p.z * cos(angle);
	rotated.y = temp_y;
	rotated.z = temp_z;
	return (rotated);
}

// Function to rotate a point around the Y axis
static t_point	rotate_y(t_point p, float angle)
{
	t_point	rotated;
	float	temp_x;
	float	temp_z;

	rotated = p;
	temp_x = p.x * cos(angle) + p.z * sin(angle);
	temp_z = -p.x * sin(angle) + p.z * cos(angle);
	rotated.x = temp_x;
	rotated.z = temp_z;
	return (rotated);
}

// Function to rotate a point around the Z axis
static t_point	rotate_z(t_point p, float angle)
{
	t_point	rotated;
	float	temp_x;
	float	temp_y;

	rotated = p;
	temp_x = p.x * cos(angle) - p.y * sin(angle);
	temp_y = p.x * sin(angle) + p.y * cos(angle);
	rotated.x = temp_x;
	rotated.y = temp_y;
	return (rotated);
}

// The main function to rotate a point
t_point	rotate_point(t_point point, t_map *map)
{
	t_point	center;
	float	rad_x;
	float	rad_y;
	float	rad_z;

	center = get_center(map);
	rad_x = deg_to_rad(map->rot_x);
	rad_y = deg_to_rad(map->rot_y);
	rad_z = deg_to_rad(map->rot_z);
	point.x -= center.x;
	point.y -= center.y;
	point.z -= center.z;
	point = rotate_x(point, rad_x);
	point = rotate_y(point, rad_y);
	point = rotate_z(point, rad_z);
	point.x += center.x;
	point.y += center.y;
	point.z += center.z;
	return (point);
}
