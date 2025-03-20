/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:53:35 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/20 22:19:49 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Converts an angle in degrees to radians.
 * @param angle Angle in degrees.
 * @return Angle in radians.
 */
float	deg_to_rad(float angle)
{
	float	math_pi;

	math_pi = 3.14159265358979323846;
	return (angle * math_pi / 180.0);
}

/**
 * @brief Converts a point in 3D space to an isometric projection.
 * @param point The point to convert.
 * @param flatten_factor The factor to flatten the z-coordinate.
 * @return The isometric projection of the point.
 */
t_point2d	to_isometric(t_point point, float flatten_factor)
{
	t_point2d	proj;
	float		iso_angle;

	iso_angle = deg_to_rad(30);
	proj.x = (int)round((point.x - point.y) * cos(iso_angle));
	proj.y = (int)round((point.x + point.y) * sin(iso_angle) - (point.z
				/ flatten_factor));
	return (proj);
}

/**
 * @brief Converts a point in 3D space to an orthographic projection.
 * @param point The point to convert.
 * @return The orthographic projection of the point.
 */
t_point2d	to_orthographic(t_point point)
{
	t_point2d	proj;

	proj.x = point.x;
	proj.y = point.y;
	return (proj);
}

/**
 * @brief Converts a point in 3D space to a parallel projection.
 * @param point The point to convert.
 * @return The parallel projection of the point.
 */
t_point2d	to_parallel(t_point point)
{
	t_point2d	proj;
	float		angle;
	float		depth_factor;

	depth_factor = 0.5;
	angle = deg_to_rad(45);
	proj.x = point.x + depth_factor * point.z * cos(angle);
	proj.y = point.y + depth_factor * point.z * sin(angle);
	return (proj);
}
