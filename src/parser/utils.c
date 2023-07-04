/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:26:55 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/04 11:49:40 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

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

// char *input_sanitizer(char *line)
// {
// 	int i;
// 	char *temp;
// 	char *val;
// 	char **tokens;
// 	char *comma;
// 	t_list *toks;
// 	t_list *iter;
// 	t_list *node;
// 	char *ret;
// 	tokens = ft_split(line, ' ');
// 	if (!tokens)
// 		return (NULL);
// 	toks = NULL;
// 	i = -1;
// 	while (tokens[++i])
// 	{
// 		comma = ft_strchr(tokens[i], ',');
// 		if (!comma)
// 		{
// 			node = ft_lstnew(ft_strdup(tokens[i]));
// 			ft_lstadd_back(&toks, node);
// 		}
// 		else
// 		{
// 			while (comma || ft_strlen(tokens[i]) > 0)
// 			{
// 				val = ft_strdup(ft_substr(tokens[i], 0, comma - tokens[i]));
// 				ft_lstadd_back(&toks, ft_lstnew(val));
// 				temp = tokens[i];
// 				tokens[i] = ft_substr(tokens[i], ft_strlen(val) + 1, -1);
// 				free(temp);
// 				comma = ft_strchr(tokens[i], ',');
// 			}
// 		}
// 	}
// 	free(line);
// 	line = ft_strdup("");
// 	iter = toks;
// 	while (iter)
// 	{
// 		line = join_and_free(line, iter->content, TRUE, FALSE);
// 		line = join_and_free(line, ft_strdup(" "), TRUE, TRUE);
// 		iter = iter->next;
// 	}
// 	ft_lstclear(&toks, free);
// 	ret = ft_substr(line, 0, ft_strlen(line) - 2);
// 	free(line);
// 	return (ret);
// }

static void clean_whitespaces(char *line)
{
	int i;

	i = -1;
	while (line[++i])
		if (ft_iswhitespace(line[i]))
			line[i] = ' ';
}

static void clean_commas(t_list **tok_list, char **tokens, int i, char *comma_pos)
{
	char *temp;
	char *val;

	while (comma_pos || ft_strlen(tokens[i]) > 0)
	{
		val = ft_strdup(ft_substr(tokens[i], 0, comma_pos - tokens[i]));
		ft_lstadd_back(&(*tok_list), ft_lstnew(val));
		temp = tokens[i];
		tokens[i] = ft_substr(tokens[i], ft_strlen(val) + 1, -1);
		free(temp);
		comma_pos = ft_strchr(tokens[i], ',');
	}
}

static char *merge_tokens(t_list **tok_list)
{
	char *line;
	char *ret;
	t_list *iterator;

	line = ft_strdup("");
	iterator = *tok_list;
	while (iterator)
	{
		line = join_and_free(line, iterator->content, TRUE, FALSE);
		line = join_and_free(line, ft_strdup(" "), TRUE, TRUE);
		iterator = iterator->next;
	}
	ft_lstclear(&(*tok_list), free);
	ret = ft_substr(line, 0, ft_strlen(line) - 1);
	free(line);
	return (ret);
}

char *input_sanitizer(char *line)
{
	char **tokens;
	int i;
	char *comma_pos;
	t_list *tok_list;
	t_list *node;

	clean_whitespaces(line);
	tok_list = NULL;
	tokens = ft_split(line, ' ');
	if (!tokens || !*tokens)
		return (NULL);
	i = -1;
	while (tokens[++i])
	{
		comma_pos = ft_strchr(tokens[i], ',');
		if (!comma_pos)
		{
			node = ft_lstnew(ft_strdup(tokens[i]));
			ft_lstadd_back(&tok_list, node);
		}
		else
			clean_commas(&tok_list, tokens, i, comma_pos);
	}
	free(line);
	return (merge_tokens(&tok_list));
}