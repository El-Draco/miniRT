/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:47:49 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/26 13:44:59 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static t_bool validate_args(int argc, char **argv)
{
	if (argc == 1 || argc > 2)
		return (FALSE);
	return (!ft_strncmp("", argv[1], 2));
}

static void parse_lines(t_scene *scene, t_list *lines)
{
	char	identifier;
	char	*line;
	while (lines)
	{
		line = (char *)(lines->content);
		identifier = line[0];
		if (identifier == 'A')
			retrieve_amb_light(scene, line);
		else if (identifier == 'C')
			retrieve_camera(scene, line);
		else if (identifier == 'L')
			retrieve_point_light(scene, line);
		else
			retrieve_shape(scene, lines);
		lines = lines->next;
	}
}

int parser(t_scene *scene, int argc, char **argv)
{
	char *line;
	t_list *lines;
	char *clean_line;
	int fd;

	if (validate_args(argc, argv))
		return (EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY, 0666);
	if (fd < 0)
	{
		printf("Error while opening file\n");
		return (EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line)
	{
		clean_line = input_sanitizer(line);
		ft_lstadd_back(&lines, ft_lstnew(clean_line));
		line = get_next_line(fd);
	}
	parse_lines(scene, lines);
	ft_lstclear(&lines, free);
	close(fd);
	return (EXIT_SUCCESS);
}