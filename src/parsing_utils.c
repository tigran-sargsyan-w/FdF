/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:43:02 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/18 19:53:36 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Determine map dimensions from the first line of the list
static void	get_map_dimensions(t_list *lines, t_map *map)
{
	char	**tokens;
	int		col;

	map->rows = ft_lstsize(lines);
	tokens = ft_split((char *)lines->content, ' ');
	if (!tokens)
		error_exit("ft_split");
	map->columns = ft_count_tokens(tokens);
	col = 0;
	while (tokens[col])
	{
		free(tokens[col]);
		col++;
	}
	free(tokens);
}

// Process one line: split and convert to integer array
static void	process_line(char *line, int *row_values, int *row_colors,
		t_vars *vars)
{
	int	column_index;

	column_index = 0;
	while (*line && column_index < vars->map->columns)
	{
		while (*line == ' ')
			line++;
		if (*line)
		{
			if (!ft_isvalid_int(line))
			{
				cleanup_and_exit(vars);
			}
			row_values[column_index] = ft_atoi(line);
		}
		row_colors[column_index] = DEFAULT_COLOR;
		while (*line && *line != ' ' && *line != ',')
			line++;
		if (*line == ',')
		{
			line++;
			if (!ft_isvalid_hex(line))
			{
				cleanup_and_exit(vars);
			}
			row_colors[column_index] = ft_atoi_hex(line);
			while (*line && *line != ' ')
				line++;
		}
		column_index++;
	}
}

// Fill the 2D array with map values from the linked list
static void	fill_map_values(t_list *lines, t_vars *vars)
{
	t_map	*map;
	int		row_index;

	map = vars->map;
	map->values = (int **)ft_calloc(map->rows, sizeof(int *));
	if (!map->values)
		error_exit("alloc for values");
	map->colors = (int **)ft_calloc(map->rows, sizeof(int *));
	if (!map->colors)
		error_exit("alloc for colors");
	row_index = 0;
	while (lines)
	{
		map->values[row_index] = (int *)ft_calloc(map->columns, sizeof(int));
		if (!map->values[row_index])
			error_exit("alloc for row values");
		map->colors[row_index] = (int *)ft_calloc(map->columns, sizeof(int));
		if (!map->colors[row_index])
			error_exit("alloc for row colors");
		process_line((char *)lines->content, map->values[row_index],
			map->colors[row_index], vars);
		row_index++;
		lines = lines->next;
	}
}

void	init_map(t_vars *vars)
{
	int		i;
	t_map	*map;

	map = vars->map;
	i = 0;
	get_map_dimensions(vars->lines, map);
	fill_map_values(vars->lines, vars);
	map->rot_x = 0;
	map->rot_y = 0;
	map->rot_z = 0;
	map->trans_x = 0;
	map->trans_y = 0;
	map->flatten_factor = 1.0;
	map->projection_mode = ISO;
	map->render_points = ft_calloc(map->rows, sizeof(t_point2d *));
	if (!map->render_points)
		error_exit("alloc failed");
	while (i < map->rows)
	{
		map->render_points[i] = ft_calloc(map->columns, sizeof(t_point2d));
		if (!map->render_points[i])
			error_exit("alloc failed");
		i++;
	}
}
