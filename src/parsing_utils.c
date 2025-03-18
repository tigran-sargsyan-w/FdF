/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:43:02 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/18 15:49:42 by tsargsya         ###   ########.fr       */
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
		int columns)
{
	int		column_index;
	char	*current_char;

	column_index = 0;
	current_char = line;
	while (*current_char && column_index < columns)
	{
		while (*current_char == ' ')
			current_char++;
		if (*current_char)
		{
			if (!ft_isvalid_int(current_char))
			{
				error_exit("Invalid value");
			}
			row_values[column_index] = ft_atoi(current_char);
		}
		row_colors[column_index] = DEFAULT_COLOR;
		while (*current_char && *current_char != ' ' && *current_char != ',')
			current_char++;
		if (*current_char == ',')
		{
			current_char++;
			if (!ft_isvalid_hex(current_char))
			{
				error_exit("Invalid color");
			}
			row_colors[column_index] = ft_atoi_hex(current_char);
			while (*current_char && *current_char != ' ')
				current_char++;
		}
		column_index++;
	}
}

// Fill the 2D array with map values from the linked list
static void	fill_map_values(t_list *lines, t_map *map)
{
	int	row_index;

	map->values = (int **)malloc(map->rows * sizeof(int *));
	if (!map->values)
		error_exit("malloc for values");
	map->colors = (int **)malloc(map->rows * sizeof(int *));
	if (!map->colors)
		error_exit("malloc for colors");
	row_index = 0;
	while (lines)
	{
		map->values[row_index] = (int *)malloc(map->columns * sizeof(int));
		if (!map->values[row_index])
			error_exit("malloc for row values");
		map->colors[row_index] = (int *)malloc(map->columns * sizeof(int));
		if (!map->colors[row_index])
			error_exit("malloc for row colors");
		process_line((char *)lines->content, map->values[row_index],
			map->colors[row_index], map->columns);
		row_index++;
		lines = lines->next;
	}
}

void	init_map(t_vars *vars, t_list *lines)
{
	int		i;
	t_map	*map;

	map = vars->map;
	i = 0;
	get_map_dimensions(lines, map);
	fill_map_values(lines, map);
	map->rot_x = 0;
	map->rot_y = 0;
	map->rot_z = 0;
	map->trans_x = 0;
	map->trans_y = 0;
	map->flatten_factor = 1.0;
	map->projection_mode = ISO;
	map->render_points = malloc(map->rows * sizeof(t_point2d *));
	if (!map->render_points)
		error_exit("malloc failed");
	while (i < map->rows)
	{
		map->render_points[i] = malloc(map->columns * sizeof(t_point2d));
		if (!map->render_points[i])
			error_exit("malloc failed");
		i++;
	}
}
