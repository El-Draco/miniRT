/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:47:49 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/04 17:51:07 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static t_bool valid_args(int argc, char **argv)
{
	char *file_name;

	if (argc == 1 || argc > 2)
		return (FALSE);
	if (!ft_strncmp("", argv[1], 2) || ft_strlen(argv[1]) <= 3)
		return (FALSE);
	file_name = ft_substr(argv[1], ft_strlen(argv[1]) - 3, 4);
	if (!ft_strncmp(file_name, ".rt", 4))
		return (TRUE);
	return (FALSE);
}

t_bool valid_char(char *str, t_bool floating)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (floating && str[i] && ft_isalpha(str[i]) && str[i] != '.')
			return (FALSE);
		if (!floating && str[i] && (ft_isalpha(str[i]) || str[i] == '.' ))
			return (FALSE);
	}
	return (TRUE);
}

t_bool check_commas(char **tokens)
{
	int i;

	i = -1;
	while (++i < 5)
		if (!tokens[i])
			return (FALSE);
	if (!ft_strncmp(tokens[0], ",", 2) || ft_strncmp(tokens[1], ",", 2))
		return (FALSE);
	if (ft_strncmp(tokens[1], ",", 2) || !ft_strncmp(tokens[2], ",", 2))
		return (FALSE);
	if (!ft_strncmp(tokens[2], ",", 2) || ft_strncmp(tokens[3], ",", 2))
		return (FALSE);
	if (ft_strncmp(tokens[3], ",", 2) || !ft_strncmp(tokens[4], ",", 2))
		return (FALSE);
	if (tokens[5] && !ft_strncmp(tokens[5], ",", 2))
		return (FALSE);
	return (TRUE);
}

t_bool invalid_rgb_range(t_rgb rgb)
{
	if (rgb.red <0.0f || rgb.red > 255.0f)
		return (TRUE);
	if (rgb.green < 0.0f || rgb.green > 255.0f)
		return (TRUE);
	if (rgb.blue < 0.0f || rgb.blue > 255.0f)
		return (TRUE);
	return (FALSE);
}

t_bool parse_rgb(char **tokens, t_rgb *rgb)
{
	if (!check_commas(tokens))
		return (FALSE);
	if (!valid_char(tokens[0], FALSE))
		return (FALSE);
	rgb->red = ft_atoi(tokens[0]);
	if (!valid_char(tokens[2], FALSE))
		return (FALSE);
	rgb->green = ft_atoi(tokens[2]);
	if (!valid_char(tokens[4], FALSE))
		return (FALSE);
	rgb->blue = ft_atoi(tokens[4]);
	if (invalid_rgb_range(*rgb))
		return (FALSE);
	return (TRUE);
}

t_bool parse_vec3(char **tokens, t_vec3 *vec)
{
	if (!check_commas(tokens))
		return (FALSE);
	if (!valid_char(tokens[0], TRUE))
		return (FALSE);
	vec->x = float_parser(tokens[0]);
	if (!valid_char(tokens[2], TRUE))
		return (FALSE);
	vec->y = float_parser(tokens[2]);
	if (!valid_char(tokens[4], TRUE))
		return (FALSE);
	vec->z = float_parser(tokens[4]);
	return (TRUE);
}

int count_dots(char *str)
{
	int i;
	int count;

	count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '.')
			count++;
	}
	return (count);
}

t_bool parse_float(char **tokens, float *num)
{
	if (!valid_char(tokens[0], TRUE))
		return (FALSE);
	if (count_dots(tokens[0]) > 1)
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

	if (!lines)
		return (FALSE);
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
		status = retrieve_shape(scene, lines);
		if (status == FALSE)
			return (FALSE);
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

	if (!valid_args(argc, argv))
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