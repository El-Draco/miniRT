/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:26:55 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/06 14:24:36 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	clean_whitespaces(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (ft_iswhitespace(line[i]))
			line[i] = ' ';
}

static void	clean_commas(t_list **tok_list, char **tokens, int i, char *c_pos)
{
	char	*temp;
	char	*val;
	char	*val_str;

	while (c_pos || ft_strlen(tokens[i]) > 0)
	{
		val_str = ft_substr(tokens[i], 0, c_pos - tokens[i]);
		val = ft_strdup(val_str);
		free(val_str);
		ft_lstadd_back(&(*tok_list), ft_lstnew(val));
		if (c_pos)
			ft_lstadd_back(&(*tok_list), ft_lstnew(ft_strdup(",")));
		temp = tokens[i];
		tokens[i] = ft_substr(tokens[i], ft_strlen(val) + 1, -1);
		free(temp);
		c_pos = ft_strchr(tokens[i], ',');
	}
}

static char	*merge_tokens(t_list **tok_list)
{
	char	*line;
	char	*ret;
	t_list	*iterator;

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

char	*input_sanitizer(char *line)
{
	char	**tokens;
	int		i;
	char	*comma_pos;
	t_list	*tok_list;
	t_list	*node;

	clean_whitespaces(line);
	tokens = ft_split(line, ' ');
	if (!tokens || !*tokens)
		return (free_split_ptr(tokens));
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
	free_split_ptr(tokens);
	return (merge_tokens(&tok_list));
}
