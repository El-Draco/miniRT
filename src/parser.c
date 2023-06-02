/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:47:49 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/02 21:03:00 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

double float_parser(char *s)
{
	int i;
	int neg;
	double d;
	double temp;

	i = 0;
	neg = 1;
	d = 0;
	if (s[i] == '-')
	{
		neg = -1;
		i++;
	}
	while (s[i] && s[i] != '.')
		d = d * 10 + (s[i++] - '0');
	if (s[i] && s[i] == '.')
		i++;
	temp = 0.1;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		d += (s[i++] - '0') * temp;
		temp /= 10;
	}
	return (neg * d);
}


char **input_sanitizer(char **tokens)
{
	int i;
	int j;
	double num;


	i = 0;

	while (tokens[++i])
	{
		j = 0;
		num = float_parser(tokens[i]);
		while(tokens[i][j] && tokens[i][j] != ',')
			j++;
		if (tokens[i][j] == ',')
			;
	}
}

t_bool retrieve_amb_light(int fd)
{
	int i;
	char *line;
	char **tokens;
	char **light_ratio;
	char *rgb;

	line = get_next_line(fd);
	if (!line || !*line)
		return (FALSE);
	tokens = ft_split(line, ' ');
	if (!tokens || !*tokens)
		return (FALSE);
	if (!ft_strncmp(tokens[0], "A", ft_strlen(tokens[0])) || !tokens[1] || !tokens[2])
		return (FALSE);
	g_scene.ambient.intensity = float_parser(tokens[1]);
	rgb = ft_strdup("");
	i = -1;
	while (tokens[++i])
		rgb = join_and_free(rgb, tokens[i], TRUE, FALSE);
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
	tokens = ft_split(rgb, ",");
	if (!tokens || !tokens[0] || !tokens[1] | !tokens[2])
		return (FALSE);
	g_scene.ambient.color = (t_rgb){ft_atoi(tokens[0]), ft_atoi(tokens[1]), ft_atoi(tokens[2])};
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
	i = -1;
}

t_bool retrieve_element(int fd, char *identifier)
{
	int i;
	char *line;
	char **tokens;
	char **light_ratio;
	char *coord;

	line = get_next_line(fd);
	if (!line || !*line)
		return (FALSE);
	tokens = ft_split(line, ' ');
	if (!tokens || !*tokens)
		return (FALSE);
	if (!ft_strncmp(tokens[0], identifier, 2) || !tokens[1] || !tokens[2] || !tokens[3])
		return (FALSE);
	coord = ft_strdup("");
	i = 0;
	while (tokens[++i])
		coord = join_and_free(coord, tokens[i], TRUE, FALSE);

	if (ft_strncmp(identifier, "C", 2))
		g_scene.camera = ;
	if (ft_strncmp(identifier, "L", 2))
		g_scene.light = ;
	return (TRUE);
}

t_bool retrieve_shapes(int fd)
{

}

void display_metadata()
{

}

int parser(char *filename)
{
	int fd;
	int error;
	fd = open(filename, O_RDONLY, 0666);
	if (fd < 0)
	{
		ft_printf("Error while opening file\n");
		return (0);
	}
	retrieve_amb_light(fd);
	retrieve_element(fd, "C");
	retrieve_element(fd, "L");
	retrieve_shapes(fd);

	display_metadata();
	close(fd);
}