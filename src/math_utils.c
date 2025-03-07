/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:53:35 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/07 12:19:50 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to transfer degrees to radians
float	deg_to_rad(float angle)
{
	return (angle * M_PI / 180.0);
}

// Function to compute isometric projection for a 3D point
t_point2d	iso_projection(t_point pt)
{
	t_point2d	proj;
	float		iso_angle;

	iso_angle = deg_to_rad(30);
	proj.x = (int)round((pt.x - pt.y) * cos(iso_angle));
	proj.y = (int)round((pt.x + pt.y) * sin(iso_angle) - (pt.z / Z_FACTOR));
	return (proj);
}
