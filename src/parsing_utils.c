/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:43:02 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/20 22:51:45 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Get the dimensions of the map from the first line of the list.
 * @param lines The linked list of lines.
 * @param vars Structure containing main variables.
 */
static void	get_map_dimensions(t_list *lines, t_vars *vars)
{
	char	**tokens;
	int		col;

	vars->map->rows = ft_lstsize(lines);
	tokens = ft_split((char *)lines->content, ' ');
	if (!tokens)
		cleanup_and_error_exit(vars, "ft_split");
	vars->map->columns = ft_count_tokens(tokens);
	col = 0;
	while (tokens[col])
	{
		free(tokens[col]);
		col++;
	}
	free(tokens);
}

/**
 * @brief Parse an integer value from the string.
 * @param pos Pointer to the position in the string.
 * @param vars Structure containing main variables.
 * @return The parsed integer value.
 */
static int	parse_int_value(char **pos, t_vars *vars)
{
	char	*line;
	int		value;

	line = *pos;
	if (!ft_isvalid_int(line))
		cleanup_and_error_exit(vars, "invalid int");
	value = ft_atoi(line);
	if (value > CLAMP_LIMIT)
		value = CLAMP_LIMIT;
	else if (value < -CLAMP_LIMIT)
		value = -CLAMP_LIMIT;
	while (*line && *line != ' ' && *line != ',')
		line++;
	*pos = line;
	return (value);
}

/**
 * @brief Parse an optional color value from the string.
 * @param pos Pointer to the position in the string.
 * @param vars Structure containing main variables.
 * @return The parsed color value or DEFAULT_COLOR if not specified.
 */
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
			cleanup_and_error_exit(vars, "invalid color");
		color = ft_atoi_hex(line);
		while (*line && *line != ' ')
			line++;
	}
	*pos = line;
	return (color);
}

/**
 * @brief Process a line of the map and fill the corresponding row values 
 * and colors.
 * @param line The line to process.
 * @param row_values The array to store the parsed integer values.
 * @param row_colors The array to store the parsed color values.
 * @param vars Structure containing main variables.
 */
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

/**
 * @brief Fill the map values and colors from the linked list of lines.
 * @param lines The linked list of lines.
 * @param vars Structure containing main variables.
 */
void	fill_map_values(t_list *lines, t_vars *vars)
{
	t_map	*map;
	int		row_index;

	map = vars->map;
	get_map_dimensions(vars->lines, vars);
	map->values = (int **)ft_calloc(map->rows, sizeof(int *));
	if (!map->values)
		cleanup_and_error_exit(vars, "alloc for values");
	map->colors = (int **)ft_calloc(map->rows, sizeof(int *));
	if (!map->colors)
		cleanup_and_error_exit(vars, "alloc for colors");
	row_index = 0;
	while (lines)
	{
		map->values[row_index] = (int *)ft_calloc(map->columns, sizeof(int));
		if (!map->values[row_index])
			cleanup_and_error_exit(vars, "alloc for row values");
		map->colors[row_index] = (int *)ft_calloc(map->columns, sizeof(int));
		if (!map->colors[row_index])
			cleanup_and_error_exit(vars, "alloc for row colors");
		process_line((char *)lines->content, map->values[row_index],
			map->colors[row_index], vars);
		row_index++;
		lines = lines->next;
	}
}
