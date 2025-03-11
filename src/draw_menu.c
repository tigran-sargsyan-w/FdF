/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:55:25 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/11 22:28:27 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	print_string(t_vars *vars, t_point2d *start, t_point2d *offset,
		char *str)
{
	start->x += offset->x;
	start->y += offset->y;
	mlx_string_put(vars->mlx, vars->win, start->x, start->y, TEXT_COLOR, str);
	start->x -= offset->x;
	offset->x = 0;
}

void	draw_menu(t_vars *vars)
{
	t_point2d	start;
	t_point2d	offset;

	start.x = 20;
	start.y = 20;
	offset.x = 70;
	offset.y = 20;
	print_string(vars, &start, &offset, "HOW TO USE:");
	print_string(vars, &start, &offset, "");
	print_string(vars, &start, &offset, "Move:");
	offset.x = 20;
	print_string(vars, &start, &offset, "A/D (X)");
	offset.x = 20;
	print_string(vars, &start, &offset, "W/S (Y)");
	print_string(vars, &start, &offset, "Rotate:");
	offset.x = 20;
	print_string(vars, &start, &offset, "ArrUp/ArrDn (X)");
	offset.x = 20;
	print_string(vars, &start, &offset, "ArrLt/ArrRt (Y)");
	offset.x = 20;
	print_string(vars, &start, &offset, "Q/E (Z)");
	print_string(vars, &start, &offset, "Zoom: +/-");
	print_string(vars, &start, &offset, "Flatten: PgUp/PgDn");
	print_string(vars, &start, &offset, "Reset: R");
	print_string(vars, &start, &offset, "Exit: ESC");
}
