/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:17:32 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/15 12:42:36 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		error_exit("mlx_init");
	mlx_get_screen_size(vars->mlx, &vars->screen_width, &vars->screen_height);
	vars->screen_width = WINDOW_WIDTH;
	vars->screen_height = WINDOW_HEIGHT;
	vars->win = mlx_new_window(vars->mlx, vars->screen_width,
			vars->screen_height, "FdF");
	if (!vars->win)
		error_exit("mlx_new_window");
	vars->data.img = mlx_new_image(vars->mlx, vars->screen_width,
			vars->screen_height);
	if (!vars->data.img)
		error_exit("mlx_new_image");
	vars->data.addr = mlx_get_data_addr(vars->data.img, &vars->data.bits_per_pixel,
			&vars->data.line_length, &vars->data.endian);
	if (!vars->data.addr)
		error_exit("mlx_get_data_addr");
	vars->shift_pressed = 0;
}

static void	load_map(t_vars *vars, char *filename)
{
	vars->map = parse_file(filename);
	if (!vars->map)
		error_exit("parse_file");
	adjust_initial_scale(vars);
}

static void	render_scene(t_vars *vars)
{
	draw_background(vars);
	update_projected_points(vars);
	draw_grid(*vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
	draw_menu(vars);
}

void	check_args(int argc, char **argv)
{
	char	*file_extension;

	if (argc != 2)
	{
		ft_printf("Usage: %s <mapname>.fdf\n", argv[0]);
		exit(1);
	}
	file_extension = ft_strrchr(argv[1], '.');
	if (!file_extension || ft_strcmp(file_extension, ".fdf") != 0)
	{
		ft_printf("File extension does not match requirements (.fdf)\n");
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	clock_t	start, end;

	start = clock();
	check_args(argc, argv);
	init_vars(&vars);
	load_map(&vars, argv[1]);
	render_scene(&vars);
	end = clock();
	printf("Time taken: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
	subscribe_to_events(&vars);
	mlx_loop(vars.mlx);
	cleanup_and_exit(&vars);
	return (0);
}
