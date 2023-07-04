/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:47:49 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/04 12:06:44 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static t_bool validate_args(int argc, char **argv)
{
	if (argc == 1 || argc > 2)
		return (FALSE);
	return (!ft_strncmp("", argv[1], 2));
}

t_bool valid_char(char *str, t_bool floating)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (floating && str[i] && ft_isalpha(str[i]) && str[i] != '.')
			return (FALSE);
		if (!floating && str[i] && str[i] == '.')
			return (FALSE);
	}
	return (TRUE);
}

t_bool parse_rgb(char **tokens, t_rgb *rgb)
{
	if (!valid_char(tokens[0], FALSE))
		return (FALSE);
	rgb->red = float_parser(tokens[0]);
	if (!valid_char(tokens[1], FALSE))
		return (FALSE);
	rgb->green = float_parser(tokens[1]);
	if (!valid_char(tokens[2], FALSE))
		return (FALSE);
	rgb->blue = float_parser(tokens[2]);
	return (TRUE);
}

t_bool parse_vec3(char **tokens, t_vec3 *vec)
{
	if (!valid_char(tokens[0], TRUE))
		return (FALSE);
	vec->x = float_parser(tokens[0]);
	if (!valid_char(tokens[1], TRUE))
		return (FALSE);
	vec->y = float_parser(tokens[1]);
	if (!valid_char(tokens[2], TRUE))
		return (FALSE);
	vec->z = float_parser(tokens[2]);
	return (TRUE);
}


t_bool parse_float(char **tokens, float *num)
{
	if (!valid_char(tokens[0], TRUE))
		return (FALSE);
	*num = float_parser(tokens[0]);
	return (TRUE);
}

t_bool parse_identifier(char **tokens, char *valid)
{
	if (!ft_strncmp(tokens[0], valid, 5))
		return (TRUE);
	return (FALSE);
}

static t_bool parse_lines(t_scene *scene, t_list *lines)
{
	char *line;
	t_bool status;

	status = retrieve_amb_light(scene, (char *)(lines->content));
	if (lines)
		lines = lines->next;
	status &= retrieve_camera(scene, (char *)(lines->content));
	if (lines)
		lines = lines->next;
	status &= retrieve_point_light(scene, (char *)(lines->content));
	if (lines)
		lines = lines->next;
	if (status == FALSE)
		return (FALSE);
	while (lines)
	{
		line = (char *)(lines->content);
		retrieve_shape(scene, lines);
		lines = lines->next;
	}
	return (status);
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
	lines = NULL;
	if (fd < 0)
	{
		printf("Error while opening file\n");
		return (EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line)
	{
		clean_line = input_sanitizer(line);
		if (clean_line)
		{
			if (!lines)
				lines = ft_lstnew(clean_line);
			else
				ft_lstadd_back(&lines, ft_lstnew(clean_line));
		}
		line = get_next_line(fd);
	}
	if (!parse_lines(scene, lines))
		return (EXIT_FAILURE);
	ft_lstclear(&lines, free);
	close(fd);
	return (EXIT_SUCCESS);
}