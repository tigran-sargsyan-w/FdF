/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:00:30 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/22 00:25:54 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point	rotate_x(t_point point, float angle);
static t_point	rotate_y(t_point point, float angle);
static t_point	rotate_z(t_point point, float angle);

/**
 * @brief Rotates a point around the X axis by a given angle.
 * @param point Point to be rotated.
 * @param angle Angle of rotation in radians.
 * @return Rotated point.
 */
static t_point	rotate_x(t_point point, float angle)
{
	t_point	rotated;
	float	temp_y;
	float	temp_z;

	rotated = point;
	temp_y = point.y * cos(angle) - point.z * sin(angle);
	temp_z = point.y * sin(angle) + point.z * cos(angle);
	rotated.y = temp_y;
	rotated.z = temp_z;
	return (rotated);
}

/**
 * @brief Rotates a point around the Y axis by a given angle.
 * @param point Point to be rotated.
 * @param angle Angle of rotation in radians.
 * @return Rotated point.
 */
static t_point	rotate_y(t_point point, float angle)
{
	t_point	rotated;
	float	temp_x;
	float	temp_z;

	rotated = point;
	temp_x = point.x * cos(angle) + point.z * sin(angle);
	temp_z = -point.x * sin(angle) + point.z * cos(angle);
	rotated.x = temp_x;
	rotated.z = temp_z;
	return (rotated);
}

/**
 * @brief Rotates a point around the Z axis by a given angle.
 * @param point Point to be rotated.
 * @param angle Angle of rotation in radians.
 * @return Rotated point.
 */
static t_point	rotate_z(t_point point, float angle)
{
	t_point	rotated;
	float	temp_x;
	float	temp_y;

	rotated = point;
	temp_x = point.x * cos(angle) - point.y * sin(angle);
	temp_y = point.x * sin(angle) + point.y * cos(angle);
	rotated.x = temp_x;
	rotated.y = temp_y;
	return (rotated);
}

/**
 * @brief Rotates a point in 3D space based on the map's rotation angles.
 * @param point Point to be rotated.
 * @param map Structure of the map containing rotation angles.
 * @return Rotated point.
 */
t_point	rotate_point(t_point point, t_map *map)
{
	t_point	center;
	float	rad_x;
	float	rad_y;
	float	rad_z;

	center.x = (map->columns - 1) * map->scale / 2;
	center.y = (map->rows - 1) * map->scale / 2;
	center.z = 0;
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
