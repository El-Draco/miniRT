/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 22:31:58 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/03 20:10:14 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>

int ft_len(const char *s);
long ft_strchr(const char *s, int c);
char *ft_strjoin(char *s1, char *s2);
char *sbstr(char *s, unsigned int start, size_t len);
char *ft_strdup(const char *s1);
void clear_saved(char **saved);
void save_leftovers(char **saved, char **buff, long pos);
void parse_saved_string(char **saved, char **line, long *pos);
void parse_buffer_string(char **saved, char **buff, char **line, long pos);
char *get_next_line(int fd);

#endif