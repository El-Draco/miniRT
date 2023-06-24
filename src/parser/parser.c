/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:47:49 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/24 19:43:08 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int parser(t_scene *scene, char *filename)
{
	char *line;
	t_list *lines;
	t_list *iter;
	char *clean_line;
	int fd;

	fd = open(filename, O_RDONLY, 0666);
	if (fd < 0)
	{
		printf("Error while opening file\n");
		return (0);
	}
	line = get_next_line(fd);
	lines = NULL;
	while (line)
	{
		clean_line = input_sanitizer(line);
		ft_lstadd_back(&lines, ft_lstnew(clean_line));
		line = get_next_line(fd);
	}
	iter = lines;
	while (iter)
	{
		printf("%s\n", iter->content);
		iter = iter->next;
	}
	retrieve_amb_light(scene, (char *)(lines->content));
	retrieve_camera(scene, (char *)(lines->next->content));
	retrieve_point_light(scene, (char *)(lines->next->next->content));
	scene->surfaces = retrieve_shapes(scene, lines->next->next->next);
	close(fd);
	return (0);
}