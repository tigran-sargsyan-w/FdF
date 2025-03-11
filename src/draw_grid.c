/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:03:19 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/11 10:27:13 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_horizontal_line(int i, int j, t_draw_context *ctx,
		t_point2d proj_current)
{
	t_point2d	proj_next;

	if (j < ctx->map->columns - 1)
	{
		proj_next = ctx->map->projected_points[i][j + 1];
		draw_line(ctx->img, proj_current, proj_next, ctx->line_color);
	}
}

static void	draw_vertical_line(int i, int j, t_draw_context *ctx,
		t_point2d proj_current)
{
	t_point2d	proj_next;

	if (i < ctx->map->rows - 1)
	{
		proj_next = ctx->map->projected_points[i + 1][j];
		draw_line(ctx->img, proj_current, proj_next, ctx->line_color);
	}
}

static void	draw_cell_lines(int i, int j, t_draw_context *ctx)
{
	t_point2d	proj_current;

	proj_current = ctx->map->projected_points[i][j];
	draw_horizontal_line(i, j, ctx, proj_current);
	draw_vertical_line(i, j, ctx, proj_current);
}

// Function to draw grid
void	draw_grid(t_vars vars, int line_color)
{
	t_draw_context	ctx;
	int				i;
	int				j;

	ctx = create_draw_context(&vars, line_color);
	i = 0;
	while (i < vars.map->rows)
	{
		j = 0;
		while (j < vars.map->columns)
		{
			draw_cell_lines(i, j, &ctx);
			j++;
		}
		i++;
	}
}
