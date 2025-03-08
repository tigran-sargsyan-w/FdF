/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:17:32 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/08 14:01:41 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	if (map->values)
	{
		while (i < map->rows)
		{
			free(map->values[i]);
			i++;
		}
		free(map->values);
	}
	free(map);
}

static void	init_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		error_exit("mlx_init");
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	if (!vars->win)
		error_exit("mlx_new_window");
	vars->img.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!vars->img.img)
		error_exit("mlx_new_image");
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
	if (!vars->img.addr)
		error_exit("mlx_get_data_addr");
}

static void	load_map(t_vars *vars, char *filename)
{
	vars->map = parse_file(filename);
	if (!vars->map)
		error_exit("parse_file");
	adjust_initial_scale(vars->map);
}

static void	render_scene(t_vars *vars, int line_color)
{
	draw_grid(*vars, line_color);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

void	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Usage: %s <mapname>.fdf\n", argv[0]);
		exit(1);
	}
}

void	cleanup_and_exit(t_vars *vars)
{
	if (!vars || !vars->mlx)
		return ;
	if (vars->img.img)
		mlx_destroy_image(vars->mlx, vars->img.img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free_map(vars->map);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		line_color;

	line_color = create_argb(0, 255, 255, 255);
	check_args(argc, argv);
	init_vars(&vars);
	load_map(&vars, argv[1]);
	render_scene(&vars, line_color);
	subscribe_to_events(&vars);
	mlx_loop(vars.mlx);
	cleanup_and_exit(&vars);
	return (0);
}
