# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/17 11:45:08 by rriyas            #+#    #+#              #
#    Updated: 2023/03/17 18:04:06 by rriyas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minirt
CC		= gcc
RM		= rm -f
SRCS	= src/events.c src/main.c src/mlx_utils.c
OBJS	= ${SRCS:.c=.o}
LIB		= lib/minilibx_opengl_20191021/libmlx.a
CFLAGS = -Wall -Wextra -Werror

$(NAME):	${OBJS} ${LIB}
			${CC} ${CFLAGS} -I lib/minilibx_opengl_20191021/ $(OBJS) -L lib/minilibx_opengl_20191021/ -lmlx -framework OpenGL -framework AppKit -o $(NAME)

${LIB}:
			make -C lib/minilibx_opengl_20191021/

all:	$(NAME)

clean:
		@${RM} ${OBJS}

fclean:	clean
		${RM} minirt

re:		fclean all

.PHONY: all clean fclean re