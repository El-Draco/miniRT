/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:47:49 by rriyas            #+#    #+#             */
/*   Updated: 2023/05/31 21:23:16 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_bool retrieve_amb_light(int fd)
{
	int i;
	char *line;
	char **tokens;
	char **light_ratio;
	line = get_next_line(fd);
	if (!line || !*line)
		return (FALSE);
	tokens = ft_split(line, ' ');
	if (!tokens || !*tokens)
		return (FALSE);
	if (!ft_strncmp(tokens[0], "A", ft_strlen(tokens[0])))
		return (FALSE);
	// light_ratio = ft_split(tokens[1], );

	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
}
t_bool retrieve_camera(int fd)
{

}
t_bool retrieve_light(int fd)
{

}
t_bool retrieve_shape(int fd)
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
	retrieve_camera(fd);
	retrieve_light(fd);
	retrieve_shape(fd);

	close(fd);
}