/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:35:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/08 13:30:00 by tsargsya         ###   ########.fr       */
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
static int	*process_line(char *line, int columns)
{
	int		*row_values;
	int		col;
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens)
		error_exit("ft_split");
	row_values = (int *)malloc(columns * sizeof(int));
	if (!row_values)
		error_exit("malloc");
	col = 0;
	while (tokens[col])
	{
		row_values[col] = ft_atoi(tokens[col]);
		free(tokens[col]);
		col++;
	}
	free(tokens);
	return (row_values);
}

// Fill the 2D array with map values from the linked list
static int	**fill_map_values(t_list *lines, int rows, int columns)
{
	int	**values;
	int	row;

	values = (int **)malloc(rows * sizeof(int *));
	if (!values)
		error_exit("malloc");
	row = 0;
	while (lines)
	{
		values[row] = process_line((char *)lines->content, columns);
		row++;
		lines = lines->next;
	}
	return (values);
}

// Main parse_file function that uses helper functions
t_map	*parse_file(const char *filename)
{
	t_list	*lines;
	t_map	*map;

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
	map->values = fill_map_values(lines, map->rows, map->columns);
	map->rot_x = 0;
	map->rot_y = 0;
	map->rot_z = 0;
	map->trans_x = 0;
	map->trans_y = 0;
	ft_lstclear(&lines, free);
	return (map);
}
