/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:03:19 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/15 15:17:47 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_horizontal_line(int i, int j, t_vars *vars, t_point2d current)
{
	t_point2d	next;

	if (j < vars->map->columns - 1)
	{
		next = vars->map->projected_points[i][j + 1];
		draw_line(vars, current, next, vars->map->colors[i][j]);
	}
}

static void	draw_vertical_line(int i, int j, t_vars *vars, t_point2d current)
{
	t_point2d	next;

	if (i < vars->map->rows - 1)
	{
		next = vars->map->projected_points[i + 1][j];
		draw_line(vars, current, next, vars->map->colors[i][j]);
	}
}

// Function to draw grid
void	draw_grid(t_vars vars)
{
	int			i;
	int			j;
	t_point2d	point;

	i = 0;
	while (i < vars.map->rows)
	{
		j = 0;
		while (j < vars.map->columns)
		{
			point = vars.map->projected_points[i][j];
			draw_horizontal_line(i, j, &vars, point);
			draw_vertical_line(i, j, &vars, point);
			j++;
		}
		i++;
	}
}
