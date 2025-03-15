/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:37:35 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/15 16:57:22 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_image(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->data.img);
	vars->data.img = mlx_new_image(vars->mlx, vars->screen_width,
			vars->screen_height);
	vars->data.addr = mlx_get_data_addr(vars->data.img,
			&vars->data.bits_per_pixel, &vars->data.line_length,
			&vars->data.endian);
	draw_background(vars);
	draw_grid(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
	draw_menu(vars);
}

void	apply_zoom(t_map *map, float factor)
{
	map->zoom_factor *= factor;
	if (map->zoom_factor < MIN_ZOOM)
		map->zoom_factor = MIN_ZOOM;
	if (map->zoom_factor > MAX_ZOOM)
		map->zoom_factor = MAX_ZOOM;
}

void	apply_flatten(t_map *map, float factor)
{
	map->flatten_factor *= factor;
	if (map->flatten_factor < MIN_FLATTEN)
		map->flatten_factor = MIN_FLATTEN;
	if (map->flatten_factor > MAX_FLATTEN)
		map->flatten_factor = MAX_FLATTEN;
}
