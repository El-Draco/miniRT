/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:47:49 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/06 14:33:20 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	clear_surfaces(t_surface *surfaces)
{
	t_surface	*surf;

	surf = surfaces;
	while (surf)
	{
		surf = surf->next;
		free(surfaces->attributes);
		free(surfaces);
		surfaces = surf;
	}
}

static t_bool	get_scene_attributes(t_scene *scene, t_list *lines)
{
	t_bool	valid;

	valid = retrieve_amb_light(scene, (char *)(lines->content));
	if (!valid)
		return (FALSE);
	if (lines->next)
		lines = lines->next;
	valid &= retrieve_camera(scene, (char *)(lines->content));
	if (!valid)
		return (FALSE);
	if (lines->next)
		lines = lines->next;
	valid &= retrieve_point_light(scene, (char *)(lines->content));
	if (!valid)
		return (FALSE);
	if (lines->next)
		lines = lines->next;
	return (valid);
}

static t_bool	parse_lines(t_scene *scene, t_list *lines)
{
	t_bool	valid;

	if (!lines)
		return (FALSE);
	valid = get_scene_attributes(scene, lines);
	if (!valid)
		return (FALSE);
	lines = lines->next->next->next;
	while (lines)
	{
		valid = retrieve_shape(scene, lines);
		if (!valid)
		{
			clear_surfaces(scene->surfaces);
			return (FALSE);
		}
		lines = lines->next;
	}
	return (valid);
}

static void	insert_line(char *line, t_list **lines)
{
	char	*cleaned_line;

	cleaned_line = input_sanitizer(line);
	if (cleaned_line)
	{
		if (!*lines)
			*lines = ft_lstnew(cleaned_line);
		else
			ft_lstadd_back(lines, ft_lstnew(cleaned_line));
	}
	else
		free(line);
}

t_bool	parse_sucesfull(t_scene *scene, int argc, char **argv)
{
	char	*line;
	t_list	*lines;
	int		fd;
	t_bool	valid;

	if (!valid_args(argc, argv))
		return (FALSE);
	fd = open(argv[1], O_RDONLY, 0666);
	lines = NULL;
	if (fd < 0)
	{
		printf("Error while opening file\n");
		return (EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line && *line)
	{
		insert_line(line, &lines);
		line = get_next_line(fd);
	}
	valid = parse_lines(scene, lines);
	ft_lstclear(&lines, free);
	close(fd);
	return (valid);
}
