/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:53:35 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/15 17:47:44 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to transfer degrees to radians
float	deg_to_rad(float angle)
{
	float	math_pi;

	math_pi = 3.14159265358979323846;
	return (angle * math_pi / 180.0);
}

// Function to compute isometric projection for a 3D point
t_point2d	to_isometric(t_point pt, float flatten_factor)
{
	t_point2d	proj;
	float		iso_angle;

	iso_angle = deg_to_rad(30);
	proj.x = (int)round((pt.x - pt.y) * cos(iso_angle));
	proj.y = (int)round((pt.x + pt.y) * sin(iso_angle) - (pt.z
				/ flatten_factor));
	return (proj);
}

t_point2d	to_orthographic(t_point pt)
{
	t_point2d	proj;

	proj.x = pt.x;
	proj.y = pt.y;
	return (proj);
}

t_point2d	to_parallel(t_point pt)
{
	t_point2d	proj;
	float		angle;
	float		depth_factor;

	depth_factor = 0.5;
	angle = deg_to_rad(45);
	proj.x = pt.x + depth_factor * pt.z * cos(angle);
	proj.y = pt.y + depth_factor * pt.z * sin(angle);
	return (proj);
}
