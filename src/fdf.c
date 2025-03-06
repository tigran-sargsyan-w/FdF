/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:17:32 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/06 12:28:49 by tsargsya         ###   ########.fr       */
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



int	main(void)
{
	t_map	*map;
	t_data	img;
	void	*mlx;
	void	*win;
	int		line_color;

	line_color = create_argb(0, 255, 255, 255);
	map = parse_file("/home/t_sargsyan/Github/FdF/maps/0.fdf");
	if (!map)
		error_exit("parse_file");
	mlx = mlx_init();
	if (!mlx)
		error_exit("mlx_init");
	win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	if (!win)
		error_exit("mlx_new_window");
	img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!img.img)
		error_exit("mlx_new_image");
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	if (!img.addr)
		error_exit("mlx_get_data_addr");
	adjust_scale(map);
	draw_grid(&img, map, line_color);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	free_map(map);
	return (0);
}
