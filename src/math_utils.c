/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:53:35 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/15 11:36:46 by tsargsya         ###   ########.fr       */
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
t_point2d	iso_projection(t_point pt, float flatten_factor)
{
	t_point2d	proj;
	float		iso_angle;

	iso_angle = deg_to_rad(30);
	proj.x = (int)round((pt.x - pt.y) * cos(iso_angle));
	proj.y = (int)round((pt.x + pt.y) * sin(iso_angle) - (pt.z
				/ flatten_factor));
	return (proj);
}

t_point2d	ortho_projection(t_point pt, t_map *map)
{
	t_point2d	proj;

	(void)map;
	proj.x = pt.x;
	proj.y = pt.y;
	return (proj);
}

t_point2d	parallel_projection(t_point pt, float depth_factor)
{
	t_point2d	proj;
	float		angle;

	angle = deg_to_rad(45);
	proj.x = pt.x + depth_factor * pt.z * cos(angle);
	proj.y = pt.y + depth_factor * pt.z * sin(angle);
	return (proj);
}
