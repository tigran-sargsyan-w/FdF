/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:43:02 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/19 20:54:04 by tsargsya         ###   ########.fr       */
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

static int	parse_int_value(char **pos, t_vars *vars)
{
	char	*line;
	int		value;

	line = *pos;
	if (!ft_isvalid_int(line))
		cleanup_and_exit(vars);
	value = ft_atoi(line);
	while (*line && *line != ' ' && *line != ',')
		line++;
	*pos = line;
	return (value);
}

static int	parse_optional_color(char **pos, t_vars *vars)
{
	char	*line;
	int		color;

	line = *pos;
	color = DEFAULT_COLOR;
	if (*line == ',')
	{
		line++;
		if (!ft_isvalid_hex(line))
			cleanup_and_exit(vars);
		color = ft_atoi_hex(line);
		while (*line && *line != ' ')
			line++;
	}
	*pos = line;
	return (color);
}

static void	process_line(char *line, int *row_values, int *row_colors,
		t_vars *vars)
{
	int	column_index;

	column_index = 0;
	while (*line && column_index < vars->map->columns)
	{
		while (*line == ' ')
			line++;
		row_values[column_index] = parse_int_value(&line, vars);
		row_colors[column_index] = parse_optional_color(&line, vars);
		column_index++;
	}
}

// Fill the 2D array with map values from the linked list
void	fill_map_values(t_list *lines, t_vars *vars)
{
	t_map	*map;
	int		row_index;

	map = vars->map;
	get_map_dimensions(vars->lines, map);
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
