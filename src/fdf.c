/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:17:32 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/01 18:02:45 by tsargsya         ###   ########.fr       */
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

void draw_filled_circle(t_vars *vars, int radius, int color)
{
    int x = -radius;
    int y;

    while (x <= radius)
    {
        y = -radius;
        while (y <= radius)
        {
            if (x * x + y * y <= radius * radius)
            {
                int pixel = ((vars->obj_y + y) * vars->data.line_length) + ((vars->obj_x + x) * (vars->data.bits_per_pixel / 8));
                if (vars->obj_x + x >= 0 && vars->obj_x + x < WINDOW_WIDTH && vars->obj_y + y >= 0 && vars->obj_y + y < WINDOW_HEIGHT)
                    *(int *)(vars->data.addr + pixel) = color;
            }
            y++;
        }
        x++;
    }
}

int	handle_close(t_vars *vars)
{
	printf("Window closed!\n");
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

int	handle_key_press(int keycode, t_vars *vars)
{
	if (keycode == KEY_W && vars->obj_y - MOVE_SPEED > 0)
        vars->obj_y -= MOVE_SPEED;
    if (keycode == KEY_S && vars->obj_y + MOVE_SPEED < WINDOW_HEIGHT)
        vars->obj_y += MOVE_SPEED;
    if (keycode == KEY_A && vars->obj_x - MOVE_SPEED > 0)
        vars->obj_x -= MOVE_SPEED;
    if (keycode == KEY_D && vars->obj_x + MOVE_SPEED < WINDOW_WIDTH)
        vars->obj_x += MOVE_SPEED;
	if (keycode == KEY_ESC)
		handle_close(vars);
	return (0);
}

int	handle_resize(t_vars *vars)
{
	printf("Window resized!\n");
	return (0);
}

int	mouse_enter(t_vars *vars)
{
	printf("Mouse entered window!\n");
	return (0);
}

int	mouse_leave(t_vars *vars)
{
	printf("Mouse left window!\n");
	return (0);
}

int mouse_move(int x, int y, t_vars *vars)
{
    (void)vars; // Если не используем vars, чтобы не было warning'ов
    printf("Mouse position: X = %d, Y = %d\n", x, y);
    return (0);
}

int render_next_frame(t_vars *vars)
{
	fill_screen(vars, 0x000000);
    int red = create_argb(0, 255, 0, 0);
    draw_filled_circle(vars,50, red);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);

    return (0);
}

int	main(void)
{
	t_vars	vars;
	int		red;
	t_map	*map;

	// char	*relative_path = "./photo.xpm";
	// int		img_width;
	// int		img_height;

	// vars.mlx = mlx_init();
	// vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
	// 		"Testing!");
	// vars.data.img = mlx_new_image(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	// vars.data.img = mlx_xpm_file_to_image(vars.mlx, relative_path, &img_width, &img_height);
	// vars.data.addr = mlx_get_data_addr(vars.data.img, &vars.data.bits_per_pixel, &vars.data.line_length,
	// 		&vars.data.endian);
	// red = create_argb(0, 255, 0, 0);
	// vars.obj_x = WINDOW_WIDTH / 2;
	// vars.obj_y = WINDOW_HEIGHT / 2;
	// draw_grid(&img, 50, 50, 10, 10, 50, 0x00FFFFFF);
	// draw_iso_cube(&img, 100, 100, 50, 30, 0xFF0000);
	// draw_circle(&img, 200, 200, 50, 0x00FF00FF);
	// draw_filled_circle(&vars, 50, red);
	// mlx_put_image_to_window(vars.mlx, vars.win, vars.data.img, 0, 0);
	
	// mlx_hook(vars.win, ON_CONFIGURE_NOTIFY,STRUCTURE_NOTIFY_MASK,handle_resize, &vars);
	// mlx_hook(vars.win, ON_KEYDOWN, KEY_PRESS_MASK, handle_key_press, &vars);
	// mlx_hook(vars.win, ON_DESTROY_NOTIFY, NO_EVENT_MASK, handle_close, &vars);
	// mlx_hook(vars.win, ON_ENTER_NOTIFY, ENTER_WINDOW_MASK, mouse_enter, &vars);
	// mlx_hook(vars.win, ON_LEAVE_NOTIFY, LEAVE_WINDOW_MASK, mouse_leave, &vars);
	// mlx_hook(vars.win, ON_MOUSEMOVE, POINTER_MOTION_MASK, mouse_move, &vars);
	// mlx_loop_hook(vars.mlx, render_next_frame, &vars);

	map = parse_file("/home/t_sargsyan/Github/FdF/maps/0.fdf");
	if (map == NULL)
		ft_printf("Map is NULL\n");
	else
	{
		ft_printf("Map is not NULL\n");
		ft_printf("value: %d\n", map->values[0][0]);
		ft_printf("value: %d\n", map->values[1][0]);
		ft_printf("value: %d\n", map->values[0][1]);
		ft_printf("value: %d\n", map->values[5][9]);
	}	
	// mlx_loop(vars.mlx);
	return (0);
}
