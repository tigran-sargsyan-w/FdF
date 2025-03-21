/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:55:25 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/21 11:25:06 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	print_string(t_vars *vars, t_point2d *start, t_point2d *offset,
				char *str);
static void	print_transform_menu(t_vars *vars, t_point2d *start,
				t_point2d *offset);
static void	print_misc_menu(t_vars *vars, t_point2d *start, t_point2d *offset);

/**
 * @brief Prints a string on the screen at the specified coordinates.
 * @param vars Structure containing main variables.
 * @param start Starting point of the string.
 * @param offset Offset for the string.
 * @param str String to be printed.
 */
static void	print_string(t_vars *vars, t_point2d *start, t_point2d *offset,
		char *str)
{
	start->x += offset->x;
	start->y += offset->y;
	mlx_string_put(vars->mlx, vars->win, start->x, start->y, TEXT_COLOR, str);
	start->x -= offset->x;
	offset->x = 0;
}

/**
 * @brief Prints the transformation menu on the screen.
 * @param vars Structure containing main variables.
 * @param start Starting point of the menu.
 * @param offset Offset for the menu.
 */
static void	print_transform_menu(t_vars *vars, t_point2d *start,
		t_point2d *offset)
{
	print_string(vars, start, offset, "");
	print_string(vars, start, offset, "Move:");
	offset->x = 20;
	print_string(vars, start, offset, "A/D (X)");
	offset->x = 20;
	print_string(vars, start, offset, "W/S (Y)");
	print_string(vars, start, offset, "Rotate: smooth");
	offset->x = 20;
	print_string(vars, start, offset, "ArrUp/ArrDn (X)");
	offset->x = 20;
	print_string(vars, start, offset, "ArrLt/ArrRt (Y)");
	offset->x = 20;
	print_string(vars, start, offset, "Q/E (Z)");
	print_string(vars, start, offset, "Rotate: 90 degrees");
	offset->x = 20;
	print_string(vars, start, offset, "Shift + ArrUp/ArrDn (X)");
	offset->x = 20;
	print_string(vars, start, offset, "Shift + ArrLt/ArrRt (Y)");
	offset->x = 20;
	print_string(vars, start, offset, "Shift + Q/E (Z)");
}

/**
 * @brief Prints the miscellaneous menu on the screen.
 * @param vars Structure containing main variables.
 * @param start Starting point of the menu.
 * @param offset Offset for the menu.
 */
static void	print_misc_menu(t_vars *vars, t_point2d *start, t_point2d *offset)
{
	char	*projection_name[3];

	projection_name[0] = "ISO";
	projection_name[1] = "PARALLEL";
	projection_name[2] = "ORTHO";
	print_string(vars, start, offset, "Zoom:");
	offset->x = 20;
	print_string(vars, start, offset, "+/-");
	offset->x = 20;
	print_string(vars, start, offset, "ScrUp/ScrDn");
	print_string(vars, start, offset, "Flatten: PgUp/PgDn");
	print_string(vars, start, offset, "Projection: P");
	print_string(vars, start, offset, "Reset: R");
	print_string(vars, start, offset, "");
	print_string(vars, start, offset, "Exit: ESC");
	print_string(vars, start, offset, "");
	print_string(vars, start, offset, "Projection:");
	offset->x = 20;
	print_string(vars, start, offset,
		projection_name[vars->map->projection_mode]);
}

/**
 * @brief Draws the menu on the screen.
 * @param vars Structure containing main variables.
 */
void	draw_menu(t_vars *vars)
{
	t_point2d	start;
	t_point2d	offset;

	start.x = 20;
	start.y = 20;
	offset.x = 70;
	offset.y = 20;
	print_string(vars, &start, &offset, "HOW TO USE:");
	print_transform_menu(vars, &start, &offset);
	print_misc_menu(vars, &start, &offset);
}
