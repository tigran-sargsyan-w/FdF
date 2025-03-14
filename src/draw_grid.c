/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:03:19 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/14 22:09:17 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_horizontal_line(int i, int j, t_vars *vars,
		t_point2d proj_current)
{
	t_point2d	proj_next;

	if (j < vars->map->columns - 1)
	{
		proj_next = vars->map->projected_points[i][j + 1];
		draw_line(vars, proj_current, proj_next, vars->map->colors[i][j]);
	}
}

static void	draw_vertical_line(int i, int j, t_vars *vars,
		t_point2d proj_current)
{
	t_point2d	proj_next;

	if (i < vars->map->rows - 1)
	{
		proj_next = vars->map->projected_points[i + 1][j];
		draw_line(vars, proj_current, proj_next, vars->map->colors[i][j]);
	}
}

static void	draw_cell_lines(int i, int j, t_vars *vars)
{
	t_point2d	proj_current;

	proj_current = vars->map->projected_points[i][j];
	draw_horizontal_line(i, j, vars, proj_current);
	draw_vertical_line(i, j, vars, proj_current);
}

// Function to draw grid
void	draw_grid(t_vars vars)
{
	int				i;
	int				j;

	i = 0;
	while (i < vars.map->rows)
	{
		j = 0;
		while (j < vars.map->columns)
		{
			draw_cell_lines(i, j, &vars);
			j++;
		}
		i++;
	}
}
