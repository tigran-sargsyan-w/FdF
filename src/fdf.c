/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:17:32 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/27 19:33:49 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	bresenham_line(t_data *data, int x_start, int y_start, int x_end,
		int y_end, int color)
{
	int	delta_x;
	int	delta_y;
	int	step_x;
	int	step_y;
	int	error;
	int	error_double;

	delta_x = abs(x_end - x_start);
	delta_y = abs(y_end - y_start);
	// Определяем направление движения по X и Y
	step_x = 1;
	if (x_start > x_end)
		step_x = -1;
	step_y = 1;
	if (y_start > y_end)
		step_y = -1;
	// Начальная ошибка
	error = delta_x - delta_y;
	// Рисуем линию
	while (x_start != x_end || y_start != y_end)
	{
		my_mlx_pixel_put(data, x_start, y_start, color);
		error_double = error * 2;
		// Корректируем X, если ошибка больше -delta_y
		if (error_double > -delta_y)
		{
			error -= delta_y;
			x_start += step_x;
		}
		// Корректируем Y, если ошибка меньше delta_x
		if (error_double < delta_x)
		{
			error += delta_x;
			y_start += step_y;
		}
	}
}

void	draw_grid(t_data *data, int start_x, int start_y, int cols, int rows,
		int cell_size, int color)
{
	int	i;

	i = 0;
	while (i <= rows)
	{
		bresenham_line(data, start_x, start_y + i * cell_size, start_x + cols
				* cell_size, start_y + i * cell_size, color);
		i++;
	}
	i = 0;
	while (i <= cols)
	{
		bresenham_line(data, start_x + i * cell_size, start_y, start_x + i
				* cell_size, start_y + rows * cell_size, color);
		i++;
	}
}

void	iso_projection(int *x, int *y, int z)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599); // 30 градусов (PI / 6)
	*y = (prev_x + prev_y) * sin(0.523599) - z;
}

void	draw_iso_cube(t_data *data, int x, int y, int size, int height,
		int color)
{
	int	shift_x;
	int	shift_y;

	int x0, y0, x1, y1, x2, y2, x3, y3;
	int x0_top, y0_top, x1_top, y1_top, x2_top, y2_top, x3_top, y3_top;
	// Нижняя грань (основание)
	x0 = x;
	y0 = y;
	x1 = x + size;
	y1 = y;
	x2 = x;
	y2 = y + size;
	x3 = x + size;
	y3 = y + size;
	// Верхняя грань (поднята на height)
	x0_top = x0;
	y0_top = y0;
	x1_top = x1;
	y1_top = y1;
	x2_top = x2;
	y2_top = y2;
	x3_top = x3;
	y3_top = y3;
	// Преобразуем в изометрические координаты
	iso_projection(&x0, &y0, 0);
	iso_projection(&x1, &y1, 0);
	iso_projection(&x2, &y2, 0);
	iso_projection(&x3, &y3, 0);
	iso_projection(&x0_top, &y0_top, height);
	iso_projection(&x1_top, &y1_top, height);
	iso_projection(&x2_top, &y2_top, height);
	iso_projection(&x3_top, &y3_top, height);
	// Смещаем куб в центр экрана
	shift_x = WINDOW_WIDTH / 2;
	shift_y = WINDOW_HEIGHT / 2;
	x0 += shift_x;
	y0 += shift_y;
	x1 += shift_x;
	y1 += shift_y;
	x2 += shift_x;
	y2 += shift_y;
	x3 += shift_x;
	y3 += shift_y;
	x0_top += shift_x;
	y0_top += shift_y;
	x1_top += shift_x;
	y1_top += shift_y;
	x2_top += shift_x;
	y2_top += shift_y;
	x3_top += shift_x;
	y3_top += shift_y;
	// Рисуем нижнюю грань
	bresenham_line(data, x0, y0, x1, y1, color);
	bresenham_line(data, x1, y1, x3, y3, color);
	bresenham_line(data, x3, y3, x2, y2, color);
	bresenham_line(data, x2, y2, x0, y0, color);
	// Рисуем верхнюю грань
	bresenham_line(data, x0_top, y0_top, x1_top, y1_top, color);
	bresenham_line(data, x1_top, y1_top, x3_top, y3_top, color);
	bresenham_line(data, x3_top, y3_top, x2_top, y2_top, color);
	bresenham_line(data, x2_top, y2_top, x0_top, y0_top, color);
	// Соединяем верхнюю и нижнюю грани (вертикальные рёбра)
	bresenham_line(data, x0, y0, x0_top, y0_top, color);
	bresenham_line(data, x1, y1, x1_top, y1_top, color);
	bresenham_line(data, x2, y2, x2_top, y2_top, color);
	bresenham_line(data, x3, y3, x3_top, y3_top, color);
}

void	draw_circle(t_data *data, int xc, int yc, int radius, int color)
{
	int	x;
	int	y;
	int	d;

	x = 0;
	y = radius;
	d = 3 - (2 * radius); // Начальное значение ошибки
	while (x <= y)
	{
		// Рисуем 8 точек симметрии
		my_mlx_pixel_put(data, xc + x, yc + y, color);
		my_mlx_pixel_put(data, xc - x, yc + y, color);
		my_mlx_pixel_put(data, xc + x, yc - y, color);
		my_mlx_pixel_put(data, xc - x, yc - y, color);
		my_mlx_pixel_put(data, xc + y, yc + x, color);
		my_mlx_pixel_put(data, xc - y, yc + x, color);
		my_mlx_pixel_put(data, xc + y, yc - x, color);
		my_mlx_pixel_put(data, xc - y, yc - x, color);
		// Обновляем ошибку
		if (d < 0)
			d = d + (4 * x) + 6;
		else
		{
			d = d + (4 * (x - y)) + 10;
			y--;
		}
		x++;
	}
}

void	draw_filled_circle(t_data *data, int xc, int yc, int radius, int color)
{
	int	x;
	int	y;
	int	d;

	x = 0;
	y = radius;
	d = 3 - (2 * radius);
	while (x <= y)
	{
		// Рисуем горизонтальные линии, заполняя круг
		bresenham_line(data, xc - x, yc + y, xc + x, yc + y, color);
		bresenham_line(data, xc - x, yc - y, xc + x, yc - y, color);
		bresenham_line(data, xc - y, yc + x, xc + y, yc + x, color);
		bresenham_line(data, xc - y, yc - x, xc + y, yc - x, color);
		if (d < 0)
			d = d + (4 * x) + 6;
		else
		{
			d = d + (4 * (x - y)) + 10;
			y--;
		}
		x++;
	}
}

int	handle_key_press(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	main(void)
{
	t_vars	vars;
	t_data	img;
	int		red;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Testing!");
	img.img = mlx_new_image(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	red = create_argb(0, 255, 0, 0);
	
	// draw_grid(&img, 50, 50, 10, 10, 50, 0x00FFFFFF);
	// draw_iso_cube(&img, 100, 100, 50, 30, 0xFF0000);
	// draw_circle(&img, 200, 200, 50, 0x00FF00FF);
	draw_filled_circle(&img, 200, 200, 50, red);
	
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, ON_KEYDOWN, KEY_PRESS_MASK, handle_key_press, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
