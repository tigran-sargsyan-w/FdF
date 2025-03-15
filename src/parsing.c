/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:35:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/15 17:42:28 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Read file and return linked list of lines
static t_list	*read_file_lines(const char *filename)
{
	int		fd;
	char	*line;
	t_list	*lines;
	t_list	*node;

	lines = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("open");
	line = get_next_line(fd);
	while (line != NULL)
	{
		node = ft_lstnew(line);
		if (!node)
		{
			free(line);
			close(fd);
			error_exit("ft_lstnew");
		}
		ft_lstadd_back(&lines, node);
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

// Determine map dimensions from the first line of the list
static void	get_map_dimensions(t_list *lines, int *rows, int *columns)
{
	char	**tokens;
	int		col;

	*rows = ft_lstsize(lines);
	tokens = ft_split((char *)lines->content, ' ');
	if (!tokens)
		error_exit("ft_split");
	*columns = ft_count_tokens(tokens);
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
			row_values[column_index] = ft_atoi(current_char);
		row_colors[column_index] = DEFAULT_COLOR;
		while (*current_char && *current_char != ' ' && *current_char != ',')
			current_char++;
		if (*current_char == ',')
		{
			current_char++;
			row_colors[column_index] = ft_atoi_hex(current_char);
			while (*current_char && *current_char != ' ')
				current_char++;
		}
		column_index++;
	}
}

// Fill the 2D array with map values from the linked list
static void	fill_map_values(t_list *lines, int rows, int columns, t_map *map)
{
	int	row_index;

	map->values = (int **)malloc(rows * sizeof(int *));
	if (!map->values)
		error_exit("malloc for values");
	map->colors = (int **)malloc(rows * sizeof(int *));
	if (!map->colors)
		error_exit("malloc for colors");
	row_index = 0;
	while (lines)
	{
		map->values[row_index] = (int *)malloc(columns * sizeof(int));
		if (!map->values[row_index])
			error_exit("malloc for row values");
		map->colors[row_index] = (int *)malloc(columns * sizeof(int));
		if (!map->colors[row_index])
			error_exit("malloc for row colors");
		process_line((char *)lines->content, map->values[row_index],
			map->colors[row_index], columns);
		row_index++;
		lines = lines->next;
	}
}

// Main parse_file function that uses helper functions
t_map	*parse_file(const char *filename)
{
	t_list	*lines;
	t_map	*map;
	int		i;

	i = 0;
	lines = read_file_lines(filename);
	if (!lines)
		error_exit("empty file");
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
	{
		ft_lstclear(&lines, free);
		error_exit("malloc");
	}
	get_map_dimensions(lines, &map->rows, &map->columns);
	fill_map_values(lines, map->rows, map->columns, map);
	map->rot_x = 0;
	map->rot_y = 0;
	map->rot_z = 0;
	map->trans_x = 0;
	map->trans_y = 0;
	map->flatten_factor = 1.0;
	map->projection_mode = ISO;
	map->projected_points = malloc(map->rows * sizeof(t_point2d *));
	if (!map->projected_points)
		error_exit("malloc failed");
	while (i < map->rows)
	{
		map->projected_points[i] = malloc(map->columns * sizeof(t_point2d));
		if (!map->projected_points[i])
			error_exit("malloc failed");
		i++;
	}
	ft_lstclear(&lines, free);
	return (map);
}
