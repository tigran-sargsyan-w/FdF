/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:17:32 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/06 16:22:06 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		free(map->values[i]);
		i++;
	}
	free(map->values);
}

int	handle_key(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	handle_close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

int	main(void)
{
	t_vars	vars;
	int		line_color;

	line_color = create_argb(0, 255, 255, 255);
	vars.map = parse_file("/home/t_sargsyan/Github/FdF/maps/0.fdf");
	if (!vars.map)
		error_exit("parse_file");
	vars.mlx = mlx_init();
	if (!vars.mlx)
		error_exit("mlx_init");
	vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	if (!vars.win)
		error_exit("mlx_new_window");
	vars.img.img = mlx_new_image(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!vars.img.img)
		error_exit("mlx_new_image");
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
			&vars.img.endian);
	if (!vars.img.addr)
		error_exit("mlx_get_data_addr");
	adjust_scale(vars.map);
	draw_grid(&vars.img, vars.map, line_color);
	
	mlx_hook(vars.win, ON_KEYDOWN, KEY_PRESS_MASK, handle_key, &vars);
	mlx_hook(vars.win, ON_DESTROY_NOTIFY, NO_EVENT_MASK, handle_close, &vars);

	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_loop(vars.mlx);
	free_map(vars.map);
	return (0);
}
