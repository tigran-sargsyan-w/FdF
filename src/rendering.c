/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:31:36 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/14 22:54:31 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Custom pixel put function: writes color to (x, y) in image buffer
void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < vars->screen_width && y >= 0 && y < vars->screen_height)
	{
		dst = vars->img.addr + (y * vars->img.line_length + x
				* (vars->img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

// Function to adjust scale of the map to fit the window
void	adjust_initial_scale(t_vars *vars)
{
	int		max_width;
	int		max_height;
	float	scale_x;
	float	scale_y;
	float	factor;

	factor = 0.8;
	max_width = vars->screen_width * factor;
	max_height = vars->screen_height * factor;
	scale_x = (float)max_width / vars->map->columns;
	scale_y = (float)max_height / vars->map->rows;
	vars->map->scale = fmin(scale_x, scale_y);
	vars->map->zoom_factor = 1.0;
}
