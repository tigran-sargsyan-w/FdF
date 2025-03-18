/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:35:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/18 19:43:49 by tsargsya         ###   ########.fr       */
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

// Main parse_file function that uses helper functions
void	parse_file(t_vars *vars, const char *filename)
{
	vars->lines = read_file_lines(filename);
	if (!vars->lines)
		error_exit("empty file");
	vars->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!vars->map)
	{
		ft_lstclear(&vars->lines, free);
		error_exit("alloc");
	}
	init_map(vars);
	ft_lstclear(&vars->lines, free);
	vars->lines = NULL;
}
