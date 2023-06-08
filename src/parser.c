/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:47:49 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/08 15:20:35 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

float float_parser(char *s)
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
	char	*ret;
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
	ret = ft_substr(line, 0, ft_strlen(line) - 2);
	free(line);
	return (ret);
}

void retrieve_amb_light(t_scene *scene, char *line)
{
	char **tokens;
	int i;

	tokens = ft_split(line, ' ');
	scene->ambient.intensity = float_parser(tokens[1]);
	scene->ambient.color.red = float_parser(tokens[2]);
	scene->ambient.color.green = float_parser(tokens[3]);
	scene->ambient.color.blue = float_parser(tokens[4]);
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
}

void retrieve_camera(t_scene *scene, char *line)
{
	char **tokens;
	int i;

	tokens = ft_split(line, ' ');
	scene->camera.origin.x = float_parser(tokens[1]);
	scene->camera.origin.y = float_parser(tokens[2]);
	scene->camera.origin.z = float_parser(tokens[3]);
	scene->camera.orientation.x = float_parser(tokens[4]);
	scene->camera.orientation.y = float_parser(tokens[5]);
	scene->camera.orientation.z = float_parser(tokens[6]);
	scene->camera.field_of_view = float_parser(tokens[7]);
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
}

void retrieve_point_light(t_scene *scene, char *line)
{
	char **tokens;
	int i;

	tokens = ft_split(line, ' ');
	scene->light.origin.x = float_parser(tokens[1]);
	scene->light.origin.y = float_parser(tokens[2]);
	scene->light.origin.z = float_parser(tokens[3]);
	scene->light.intensity = float_parser(tokens[4]);
	scene->light.color.red = float_parser(tokens[5]);
	scene->light.color.green = float_parser(tokens[6]);
	scene->light.color.blue = float_parser(tokens[7]);
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

t_surface *retrieve_shapes(t_scene *scene, t_list *lines)
{
	int i;
	char **tokens;
	t_surface *surfaces;
	t_surface *surf;
	t_list *iter;
	t_surface *head;

	surfaces = NULL;
	iter = lines;
	scene->num_surfaces = 0;
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
		i = -1;
		while (tokens[++i])
			free(tokens[i]);
		free(tokens);
		if (surfaces == NULL)
		{
			surfaces = surf;
			head = surfaces;
		}
		else
		{
			surfaces->next = surf;
			scene->num_surfaces++;
			surfaces = surfaces->next;
		}
		iter = iter->next;
	}
	surfaces->next = NULL;
	return (head);
}

void display_metadata(t_scene *scene)
{
	t_ambi_light a;
	t_camera c;
	t_point_light l;
	t_surface *iter;
	t_vec3 *attr;
	t_cylinder *cyl;

	c = scene->camera;
	a = scene->ambient;
	l = scene->light;
	iter = scene->surfaces;
	printf("Raytracer Scene Data:\n\n");
	printf("Ambient Lighting\n\tRGB: %d,%d,%d\t\t\tIntensity: %f\n",scene->ambient.color.red,scene->ambient.color.green,scene->ambient.color.blue, scene->ambient.intensity);

	printf("Camera\n\tOrigin: %f,%f,%f\tOrientation: %f,%f,%f\t\tFOV: %d\n", c.origin.x, c.origin.y, c.origin.z, c.orientation.x, c.orientation.y, c.orientation.z, c.field_of_view);
	printf("Point Light\n\tOrigin: %f,%f,%f\tBrightness: %f\t\t\t\tRGB: %d,%d,%d\n", l.origin.x, l.origin.y, l.origin.z, l.intensity, l.color.red, l.color.green, l.color.blue);

	printf("\nShapes:\n\n");
	while (iter)
	{
		if (iter->type == SPHERE)
		{
			printf("SPHERE\t\t");
			printf("Diameter: %f\t", *((float*)(iter->attributes)));
		}
		if (iter->type == PLANE)
		{
			printf("PLANE\t\t");
			attr = (t_vec3*)(iter->attributes);
			printf("Normal Vector: %f,%f,%f\t", attr->x, attr->y, attr->z);
		}
		if (iter->type == CYLINDER)
		{
			printf("CYLINDER\t");
			cyl = (t_cylinder*)(iter->attributes);
			printf("Normal Vector: %f,%f,%f\t Diameter: %f\t Height: %f\t", attr->x, attr->y, attr->z, cyl->diameter, cyl->height);
		}
		printf("\tOrigin: %f,%f,%f\t RGB: %d,%d,%d\n", l.origin.x, l.origin.y, l.origin.z, l.color.red, l.color.green, l.color.blue);
		iter = iter->next;
	}

}

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
	display_metadata(scene);
	close(fd);
	return (0);
}