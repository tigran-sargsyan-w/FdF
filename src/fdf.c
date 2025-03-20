/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:17:32 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/20 12:03:48 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	adjust_initial_scale(t_vars *vars)
{
	int		max_width;
	int		max_height;
	float	scale_x;
	float	scale_y;
	float	factor;

	factor = 0.6;
	max_width = vars->screen_width * factor;
	max_height = vars->screen_height * factor;
	scale_x = (float)max_width / vars->map->columns;
	scale_y = (float)max_height / vars->map->rows;
	vars->map->scale = fmin(scale_x, scale_y);
	vars->map->zoom_factor = 1.0;
}

static void	init_vars(t_vars *vars, char *filename)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		cleanup_and_error_exit(vars, "mlx_init");
	mlx_get_screen_size(vars->mlx, &vars->screen_width, &vars->screen_height);
	vars->screen_width = WINDOW_WIDTH;
	vars->screen_height = WINDOW_HEIGHT;
	vars->win = mlx_new_window(vars->mlx, vars->screen_width,
			vars->screen_height, "FdF");
	if (!vars->win)
		cleanup_and_error_exit(vars, "mlx_new_window");
	vars->data.img = mlx_new_image(vars->mlx, vars->screen_width,
			vars->screen_height);
	if (!vars->data.img)
		cleanup_and_error_exit(vars, "mlx_new_image");
	vars->data.addr = mlx_get_data_addr(vars->data.img,
			&vars->data.bits_per_pixel,
			&vars->data.line_length,
			&vars->data.endian);
	if (!vars->data.addr)
		cleanup_and_error_exit(vars, "mlx_get_data_addr");
	vars->shift_pressed = 0;
	parse_file(vars, filename);
	if (!vars->map)
		cleanup_and_error_exit(vars, "parse_file");
	adjust_initial_scale(vars);
}

static void	check_args(int argc, char **argv)
{
	char	*file_extension;

	if (argc != 2)
	{
		ft_printf("Usage: %s <mapname>.fdf\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	file_extension = ft_strrchr(argv[1], '.');
	if (!file_extension || ft_strcmp(file_extension, ".fdf") != 0)
	{
		ft_printf("File extension does not match requirements (.fdf)\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	clock_t	start;
	clock_t	end;

	start = clock();
	check_args(argc, argv);
	ft_bzero(&vars, sizeof(t_vars));
	init_vars(&vars, argv[1]);
	update_scene(&vars);
	end = clock();
	printf("Time taken: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
	subscribe_to_events(&vars);
	mlx_loop(vars.mlx);
	cleanup_and_exit(&vars);
	return (0);
}
