/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:47:49 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/03 23:39:45 by rriyas           ###   ########.fr       */
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

char *input_sanitizer(char *line)
{
	int i;
	char *temp;
	char *val;
	char **tokens;
	char *comma;
	t_list *toks;
	t_list *iter;
	t_list *node;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (NULL);
	toks = NULL;
	i = -1;
	while (tokens[++i])
	{
		comma = ft_strchr(tokens[i], ',');
		if (!comma)
		{
			node = ft_lstnew(ft_strdup(tokens[i]));
			ft_lstadd_back(&toks, node);
		}
		else
		{
			while (comma || ft_strlen(tokens[i]) > 0)
			{
				val = ft_strdup(ft_substr(tokens[i], 0, comma - tokens[i]));
				ft_lstadd_back(&toks, ft_lstnew(val));
				temp = tokens[i];
				tokens[i] = ft_substr(tokens[i], ft_strlen(val) + 1, -1);
				free(temp);
				comma = ft_strchr(tokens[i], ',');
			}

		}
	}
	free(line);
	line = ft_strdup("");
	iter = toks;
	while (iter)
	{
		line = join_and_free(line, iter->content, TRUE, FALSE);
		line = join_and_free(line, ft_strdup(" "), TRUE, TRUE);
		iter = iter->next;
	}
	ft_lstclear(&toks, free);
	return (line);
}

void retrieve_amb_light(char *line)
{
	char **tokens;
	int i;

	tokens = ft_split(line, ' ');
	g_scene.ambient.intensity = float_parser(tokens[1]);
	g_scene.ambient.color.red = float_parser(tokens[2]);
	g_scene.ambient.color.green = float_parser(tokens[3]);
	g_scene.ambient.color.blue = float_parser(tokens[4]);
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
}

void retrieve_camera(char *line)
{
	char **tokens;
	int i;

	tokens = ft_split(line, ' ');
	g_scene.camera.origin.x = float_parser(tokens[1]);
	g_scene.camera.origin.y = float_parser(tokens[2]);
	g_scene.camera.origin.z = float_parser(tokens[3]);
	g_scene.camera.orientation.x = float_parser(tokens[4]);
	g_scene.camera.orientation.y = float_parser(tokens[5]);
	g_scene.camera.orientation.z = float_parser(tokens[6]);
	g_scene.camera.field_of_view = float_parser(tokens[7]);
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
}

void retrieve_point_light(char *line)
{
	char **tokens;
	int i;

	tokens = ft_split(line, ' ');
	g_scene.light.origin.x = float_parser(tokens[1]);
	g_scene.light.origin.y = float_parser(tokens[2]);
	g_scene.light.origin.z = float_parser(tokens[3]);
	g_scene.light.intensity = float_parser(tokens[4]);
	g_scene.light.color.red = float_parser(tokens[5]);
	g_scene.light.color.green = float_parser(tokens[6]);
	g_scene.light.color.blue = float_parser(tokens[7]);
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
}

t_surface *retrieve_sphere(char **tokens)
{

	float *diameter;
	t_surface *surf;

	surf = malloc(sizeof(t_surface));
	surf->type = SPHERE;
	surf->origin.x = float_parser(tokens[1]);
	surf->origin.y = float_parser(tokens[2]);
	surf->origin.z = float_parser(tokens[3]);
	diameter = malloc(sizeof(float) * 1);
	*diameter = float_parser(tokens[4]);
	surf->attributes = diameter;
	surf->color.red = float_parser(tokens[5]);
	surf->color.green = float_parser(tokens[6]);
	surf->color.blue = float_parser(tokens[7]);

	return (surf);
}

t_surface *retrieve_plane(char **tokens)
{
	t_vec3 *orientation;
	t_surface *surf;

	surf = malloc(sizeof(t_surface));
	surf->type = PLANE;
	surf->origin.x = float_parser(tokens[1]);
	surf->origin.y = float_parser(tokens[2]);
	surf->origin.z = float_parser(tokens[3]);
	orientation = malloc(sizeof(t_vec3) * 1);
	orientation->x = float_parser(tokens[4]);
	orientation->y = float_parser(tokens[5]);
	orientation->z = float_parser(tokens[6]);
	surf->attributes = orientation;
	surf->color.red = float_parser(tokens[7]);
	surf->color.green = float_parser(tokens[8]);
	surf->color.blue = float_parser(tokens[9]);
	return (surf);
}

t_surface *retrieve_cylinder(char **tokens)
{
	t_cylinder *props;
	t_surface *surf;

	surf = malloc(sizeof(t_surface));
	surf->type = CYLINDER;
	surf->origin.x = float_parser(tokens[1]);
	surf->origin.y = float_parser(tokens[2]);
	surf->origin.z = float_parser(tokens[3]);
	props = malloc(sizeof(t_cylinder) * 1);
	props->orientation.x = float_parser(tokens[4]);
	props->orientation.y = float_parser(tokens[5]);
	props->orientation.z = float_parser(tokens[6]);
	props->diameter = float_parser(tokens[7]);
	props->height = float_parser(tokens[8]);
	surf->attributes = props;
	surf->color.red = float_parser(tokens[9]);
	surf->color.green = float_parser(tokens[10]);
	surf->color.blue = float_parser(tokens[11]);
	return (surf);
}

t_surface *retrieve_shapes(t_list *lines)
{
	int i;
	char **tokens;
	t_surface *surfaces;
	t_surface *surf;
	t_list *iter;

	surfaces = NULL;
	iter = lines;
	g_scene.num_surfaces = 0;
	while (iter)
	{
		tokens = ft_split((char *)(iter->content), ' ');
		if (!tokens || !tokens[0])
			break ;
		if (!ft_strncmp(tokens[0], "sp", 3))
			surf = retrieve_sphere(tokens);
		else if (!ft_strncmp(tokens[0], "pl", 3))
			surf = retrieve_plane(tokens);
		else if (!ft_strncmp(tokens[0], "cy", 3))
			surf = retrieve_cylinder(tokens);
		if (surfaces == NULL)
			surfaces = surf;
		i = -1;
		while (tokens[++i])
			free(tokens[i]);
		free(tokens);
		iter = iter->next;
		surf = surf->next;
		g_scene.num_surfaces++;
	}
	surf = NULL;
	return (surfaces);
}

void display_metadata()
{
	t_ambi_light a;
	t_camera c;
	t_point_light l;
	t_surface *iter;
	t_vec3 *attr;
	t_cylinder *cyl;

	c = g_scene.camera;
	a = g_scene.ambient;
	l = g_scene.light;
	iter = g_scene.surfaces;
	ft_printf("Raytracer Scene Data:\n\n");
	ft_printf("Ambient Lighting\t RGB: %d,%d,%d\t Intensity: %f\n",g_scene.ambient.color.red,g_scene.ambient.color.green,g_scene.ambient.color.blue, g_scene.ambient.intensity);
	ft_printf("Camera\t Origin: %d,%d,%d\t Orientation: %d,%d,%d\t FOV: %d\n", c.origin.x, c.origin.y, c.origin.z, c.orientation.x, c.orientation.y, c.orientation.z, c.field_of_view);
	ft_printf("Point Light\t Origin: %d,%d,%d\t Brightness: %f\t RGB: %d,%d,%d\n", l.origin.x, l.origin.y, l.origin.z, l.intensity, l.color.red, l.color.green, l.color.blue);

	ft_printf("Shapes:\n\n");
	while (iter)
	{
		if (iter->type == SPHERE)
		{
			ft_printf("SPHERE\t");
			ft_printf("Diameter: %f\t", *((float*)(iter->attributes)));
		}
		if (iter->type == PLANE)
		{
			ft_printf("PLANE\t");
			attr = (t_vec3*)(iter->attributes);
			ft_printf("Normal Vector: %d,%d,%d\t", attr->x, attr->y, attr->z);
		}
		if (iter->type == CYLINDER)
		{
			ft_printf("CYLINDER\t");
			cyl = (t_cylinder*)(iter->attributes);
			ft_printf("Normal Vector: %d,%d,%d\t Diameter: %f\t Height: %f\t", attr->x, attr->y, attr->z, cyl->diameter, cyl->height);
		}
		ft_printf("Origin: %d,%d,%d\t RGB: %d,%d,%d\n", l.origin.x, l.origin.y, l.origin.z, l.color.red, l.color.green, l.color.blue);
		iter = iter->next;
	}

}

int parser(char *filename)
{
	char *line;
	t_list *lines;
	t_list *iter;
	char *clean_line;
	int fd;

	fd = open(filename, O_RDONLY, 0666);
	if (fd < 0)
	{
		ft_printf("Error while opening file\n");
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
		ft_printf("%s\n", iter->content);
		iter = iter->next;
	}
	retrieve_amb_light((char *)(lines->content));
	retrieve_camera((char *)(lines->next->content));
	retrieve_point_light((char *)(lines->next->next->content));
	g_scene.surfaces = retrieve_shapes(lines->next->next->next);

	display_metadata();
	close(fd);
	return (0);
}