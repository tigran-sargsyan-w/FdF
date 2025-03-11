/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:37:35 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/11 19:08:04 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_image(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
	draw_grid(*vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

void	apply_zoom(t_map *map, float factor)
{
	map->zoom_factor *= factor;
	if (map->zoom_factor < MIN_ZOOM)
		map->zoom_factor = MIN_ZOOM;
	if (map->zoom_factor > MAX_ZOOM)
		map->zoom_factor = MAX_ZOOM;
}
