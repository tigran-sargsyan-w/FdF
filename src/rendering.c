/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:31:36 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/14 22:41:58 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Custom pixel put function: writes color to (x, y) in image buffer
void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = vars->img.addr + (y * vars->img.line_length + x
				* (vars->img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

// Function to adjust scale of the map to fit the window
void	adjust_initial_scale(t_map *map)
{
	int		max_width;
	int		max_height;
	float	scale_x;
	float	scale_y;
	float	factor;

	factor = 0.5;
	max_width = WINDOW_WIDTH * factor;
	max_height = WINDOW_HEIGHT * factor;
	scale_x = (float)max_width / map->columns;
	scale_y = (float)max_height / map->rows;
	map->scale = fmin(scale_x, scale_y);
	map->zoom_factor = 1.0;
}
