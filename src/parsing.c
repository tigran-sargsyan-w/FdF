/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:35:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/20 11:25:25 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Read file and return linked list of lines
static t_list	*read_file_lines(t_vars *vars, const char *filename)
{
	int		fd;
	char	*line;
	t_list	*lines;
	t_list	*node;

	lines = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		cleanup_and_error_exit(vars, "open");
	line = get_next_line(fd);
	while (line != NULL)
	{
		node = ft_lstnew(line);
		if (!node)
		{
			free(line);
			close(fd);
			cleanup_and_error_exit(vars, "ft_lstnew");
		}
		ft_lstadd_back(&lines, node);
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

static void	init_map(t_vars *vars)
{
	int		i;
	t_map	*map;

	map = vars->map;
	i = 0;
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
		cleanup_and_error_exit(vars, "alloc");
	while (i < map->rows)
	{
		map->render_points[i] = ft_calloc(map->columns, sizeof(t_point2d));
		if (!map->render_points[i])
			cleanup_and_error_exit(vars, "alloc");
		i++;
	}
}

// Main parse_file function that uses helper functions
void	parse_file(t_vars *vars, const char *filename)
{
	vars->lines = read_file_lines(vars, filename);
	if (!vars->lines)
		cleanup_and_error_exit(vars, "empty file");
	vars->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!vars->map)
	{
		ft_lstclear(&vars->lines, free);
		cleanup_and_error_exit(vars, "alloc");
	}
	init_map(vars);
	ft_lstclear(&vars->lines, free);
	vars->lines = NULL;
}
