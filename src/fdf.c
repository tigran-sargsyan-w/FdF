/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:17:32 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/05 12:26:28 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(void)
{
	t_map	*map;
	void *mlx;
	void *win;
	t_data img;
	t_point pt0 = {0, 0, 0};
    t_point pt1 = {100, 100, 20};
	t_point2d start;
	t_point2d end;
	double angle = 0.523599; // 30 degrees in radians
	int line_color = 0xFF0000; // Red color

	map = parse_file("/home/t_sargsyan/Github/FdF/maps/0.fdf");
	if (!map)
		error_exit("parse_file");

	

	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, 800, 600, "FdF");
	if (!win)
		return (1);
	img.img = mlx_new_image(mlx, 800, 600);
	if (!img.img)
		return (1);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	ft_printf("bits_per_pixel: %d\n", img.bits_per_pixel);
	ft_printf("line_length: %d\n", img.line_length);
	ft_printf("endian: %d\n", img.endian);
	start = iso_projection(pt0, angle);
	end = iso_projection(pt1, angle);
	draw_line(&img, start, end, line_color);
	mlx_put_image_to_window(mlx, win, img.img, 100, 100);
	mlx_loop(mlx);
	return (0);
}
