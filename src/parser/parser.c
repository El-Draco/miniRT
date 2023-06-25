/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:47:49 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/25 13:53:20 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static t_bool validate_args(int argc, char **argv)
{
	if (argc == 1 || argc > 2)
		return (FALSE);
	return (!ft_strncmp("", argv[1], 2));
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
		return (0);
	}
	lines = NULL;
	line = get_next_line(fd);
	while (line)
	{
		clean_line = input_sanitizer(line);
		ft_lstadd_back(&lines, ft_lstnew(clean_line));
		line = get_next_line(fd);
	}
	retrieve_amb_light(scene, (char *)(lines->content));
	retrieve_camera(scene, (char *)(lines->next->content));
	retrieve_point_light(scene, (char *)(lines->next->next->content));
	scene->surfaces = retrieve_shapes(scene, lines->next->next->next);
	close(fd);
	return (EXIT_SUCCESS);
}